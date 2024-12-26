using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Transactions;

namespace rt;

public class RawCtMask : Geometry
{
    private readonly Vector _position;
    private readonly double _scale;
    private readonly ColorMap _colorMap;
    private readonly byte[] _data;

    private readonly int[] _resolution = new int[3];
    private readonly double[] _thickness = new double[3];
    private readonly Vector _v0;
    private readonly Vector _v1;

    public RawCtMask(string datFile, string rawFile, Vector position, double scale, ColorMap colorMap) : base(Color.NONE)
    {
        _position = position;
        _scale = scale;
        _colorMap = colorMap;

        var lines = File.ReadLines(datFile);
        foreach (var line in lines)
        {
            var kv = Regex.Replace(line, "[:\\t ]+", ":").Split(":");
            if (kv[0] == "Resolution")
            {
                _resolution[0] = Convert.ToInt32(kv[1]);
                _resolution[1] = Convert.ToInt32(kv[2]);
                _resolution[2] = Convert.ToInt32(kv[3]);
            }
            else if (kv[0] == "SliceThickness")
            {
                _thickness[0] = Convert.ToDouble(kv[1]);
                _thickness[1] = Convert.ToDouble(kv[2]);
                _thickness[2] = Convert.ToDouble(kv[3]);
            }
        }

        _v0 = position;
        _v1 = position + new Vector(_resolution[0] * _thickness[0] * scale, _resolution[1] * _thickness[1] * scale, _resolution[2] * _thickness[2] * scale);

        var len = _resolution[0] * _resolution[1] * _resolution[2];
        _data = new byte[len];
        using FileStream f = new FileStream(rawFile, FileMode.Open, FileAccess.Read);
        if (f.Read(_data, 0, len) != len)
        {
            throw new InvalidDataException($"Failed to read the {len}-byte raw data");
        }
    }

    private ushort Value(int x, int y, int z)
    {
        if (x < 0 || y < 0 || z < 0 || x >= _resolution[0] || y >= _resolution[1] || z >= _resolution[2])
        {
            return 0;
        }

        return _data[z * _resolution[1] * _resolution[0] + y * _resolution[0] + x];
    }


    public override Intersection GetIntersection(Line line, double minDist, double maxDist)
    {
        // Calculate the entry and exit distances (tMin, tMax) along the X axis
        // The bounding box is defined by _v0 (min corner) and _v1 (max corner)
        double tMin = (line.Dx.X >= 0 ? _v0.X - line.X0.X : _v1.X - line.X0.X) / line.Dx.X;
        double tMax = (line.Dx.X >= 0 ? _v1.X - line.X0.X : _v0.X - line.X0.X) / line.Dx.X;

        // Calculate the entry and exit distances along the Y axis
        double tyMin = (line.Dx.Y >= 0 ? _v0.Y - line.X0.Y : _v1.Y - line.X0.Y) / line.Dx.Y;
        double tyMax = (line.Dx.Y >= 0 ? _v1.Y - line.X0.Y : _v0.Y - line.X0.Y) / line.Dx.Y;

        // Check if the line misses the bounding box in the X-Y plane
        if ((tMin > tyMax) || (tyMin > tMax)) return Intersection.NONE;

        // Adjust tMin and tMax to reflect overlap in the X-Y plane
        if (tyMin > tMin) tMin = tyMin;
        if (tyMax < tMax) tMax = tyMax;

        // Calculate the entry and exit distances along the Z axis
        double tzMin = (line.Dx.Z >= 0 ? _v0.Z - line.X0.Z : _v1.Z - line.X0.Z) / line.Dx.Z;
        double tzMax = (line.Dx.Z >= 0 ? _v1.Z - line.X0.Z : _v0.Z - line.X0.Z) / line.Dx.Z;

        // Check if the line misses the bounding box in the 3D volume
        if ((tMin > tzMax) || (tzMin > tMax)) return Intersection.NONE;

        // Adjust tMin and tMax to reflect overlap in all three dimensions
        if (tzMin > tMin) tMin = tzMin;
        if (tzMax < tMax) tMax = tzMax;

        // Ensure the intersection is within the specified distance range
        if (tMin < minDist || tMax > maxDist) return Intersection.NONE;

        // Initialize the position at the starting point of the intersection
        Vector pos = line.CoordinateToPosition(tMin);
        int[] idx = GetIndexes(pos); // Convert position to voxel grid indexes
        double stepSize = Math.Min(_thickness[0], Math.Min(_thickness[1], _thickness[2])) * _scale;
        // Traverse through the voxel grid along the line
        while (tMin <= tMax)
        {
            // Fetch the voxel value at the current grid position
            ushort voxelValue = Value(idx[0], idx[1], idx[2]);

            // Check if the voxel is non-empty
            if (voxelValue > 0)
            {
                // Calculate the precise intersection point and normal at this voxel
                Vector intersectionPos = line.CoordinateToPosition(tMin);
                Vector normal = GetNormal(intersectionPos);

                // Fetch the voxel color from the color map
                Color voxelColor = _colorMap.GetColor(voxelValue);

                // Construct a material for the voxel based on its color
                Material voxelMaterial = Material.FromColor(voxelColor);

                
                return new Intersection(
                    valid: true,
                    visible: true,
                    geometry: this,
                    line: line,
                    t: tMin,
                    normal: normal,
                    material: voxelMaterial,
                    color: voxelColor
                );
            }

            // Advance to the next voxel along the line
            tMin += stepSize;  
            pos = line.CoordinateToPosition(tMin); // Update position
            idx = GetIndexes(pos); // Update voxel grid indexes
        }

       
        return Intersection.NONE;
    }



    private int[] GetIndexes(Vector v)
    {
        return new[]{
            (int)Math.Floor((v.X - _position.X) / _thickness[0] / _scale),
            (int)Math.Floor((v.Y - _position.Y) / _thickness[1] / _scale),
            (int)Math.Floor((v.Z - _position.Z) / _thickness[2] / _scale)};
    }
    public Color GetColor(Vector v)
    {
        int[] idx = GetIndexes(v);

        ushort value = Value(idx[0], idx[1], idx[2]);
        return _colorMap.GetColor(value);
    }

    private Vector GetNormal(Vector v)
    {
        int[] idx = GetIndexes(v);
        double x0 = Value(idx[0] - 1, idx[1], idx[2]);
        double x1 = Value(idx[0] + 1, idx[1], idx[2]);
        double y0 = Value(idx[0], idx[1] - 1, idx[2]);
        double y1 = Value(idx[0], idx[1] + 1, idx[2]);
        double z0 = Value(idx[0], idx[1], idx[2] - 1);
        double z1 = Value(idx[0], idx[1], idx[2] + 1);

        return new Vector(x1 - x0, y1 - y0, z1 - z0).Normalize();
    }
}