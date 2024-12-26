using System;

namespace rt
{
    public class Sphere : Ellipsoid
    {
        public Vector Center { get; private set; }  
        public double Radius { get; private set; }  

        
        public Sphere(Vector center, double radius, Material material, Color color)
            : base(center, new Vector(1, 1, 1),radius,material, color)
        {
            Center = center;
            Radius = radius;
        }

        
        public Sphere(Vector center, double radius, Color color)
            : base(center, new Vector(1, 1, 1),radius, color)
        {
            Center = center;
            Radius = radius;
        }

       
        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            //Calculate quadratic equation coefficients for intersection test
            var a = line.Dx * line.Dx;
            var b = (line.Dx * line.X0) * 2 - (line.Dx * Center) * 2;
            var c = (line.X0 * line.X0) + (Center * Center) - (Radius * Radius) - (line.X0 * Center) * 2;

            //Calculate discriminant to check if there's an intersection
            var discriminant = (b * b) - (4.0 * a * c);
            if (discriminant < 0.001)
                return Intersection.NONE;  // No intersection if discriminant is negative or very small

            //Solve for the two potential intersection points (t1 and t2)
            var sqrtDiscriminant = Math.Sqrt(discriminant);
            var t1 = (-b - sqrtDiscriminant) / (2.0 * a);
            var t2 = (-b + sqrtDiscriminant) / (2.0 * a);

            //Check if t1 and/or t2 are within the valid distance range
            bool validT1 = t1 >= minDist && t1 <= maxDist;
            bool validT2 = t2 >= minDist && t2 <= maxDist;

            // Return NONE if neither intersection is within the range
            if (!validT1 && !validT2)
                return Intersection.NONE;

            // Choose the closest valid intersection distance (t)
            double t;
            if (validT1 && (!validT2 || t1 < t2))
                t = t1;   
            else
                t = t2;  

            //Calculate intersection properties at chosen t
            var position = line.CoordinateToPosition(t);  // Position of intersection on the sphere
            var normal = (position - Center).Normalize();  
            var material = this.Material; 
            var color = this.Color;

            
            return new Intersection(
                valid: true,
                visible: true,
                geometry: this,
                line: line,
                t: t,
                normal: normal,
                material: material,
                color: color
            );
        }
    }
}
