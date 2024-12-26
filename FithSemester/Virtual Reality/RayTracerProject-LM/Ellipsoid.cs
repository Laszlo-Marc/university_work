using System;

namespace rt
{
    public class Ellipsoid : Geometry
    {
        public Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }


        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            // Semi-axis lengths for the ellipse
            var a = SemiAxesLength.X * Radius;
            var b = SemiAxesLength.Y * Radius;
            var c = SemiAxesLength.Z * Radius;

            // Normalizing the line direction and start point relative to the ellipse dimensions
            var Dx = new Vector(line.Dx.X / a, line.Dx.Y / b, line.Dx.Z / c);
            var X0 = new Vector((line.X0.X - Center.X) / a, (line.X0.Y - Center.Y) / b, (line.X0.Z - Center.Z) / c);

            // Coefficients of the quadratic equation
            var A = Dx * Dx;
            var B = 2 * (X0 * Dx);
            var C = (X0 * X0) - 1; // For an ellipse, this is equivalent to (X0 * X0) - 1

            // Discriminant of the quadratic equation
            var discriminant = (B * B) - (4.0 * A * C);

            // If the discriminant is negative, no real roots exist, so no intersection
            if (discriminant < 0.0)
                return new Intersection(false, false, this, line, 0, line.Dx, Material, Color);

            // Solving for t values (distance along the line)
            var sqrtDiscriminant = Math.Sqrt(discriminant);
            var t1 = (-B - sqrtDiscriminant) / (2.0 * A);
            var t2 = (-B + sqrtDiscriminant) / (2.0 * A);

            // Check if t1 or t2 falls within the valid range [minDist, maxDist]
            var validT1 = t1 >= minDist && t1 <= maxDist;
            var validT2 = t2 >= minDist && t2 <= maxDist;

            // No valid intersection if both t1 and t2 are out of range
            if (!validT1 && !validT2)
                return new Intersection(false, false, this, line, 0, line.Dx, Material, Color);

            // Choose the closest valid intersection (smallest t)
            double t = validT1 ? t1 : t2;
            if (validT1 && validT2)
                t = Math.Min(t1, t2);

            // Calculate the intersection point and the normal at that point (in unnormalized space)
            var intersectionPoint = line.X0 + line.Dx * t;
            var normal = new Vector(
                (intersectionPoint.X - Center.X) / (a * a),
                (intersectionPoint.Y - Center.Y) / (b * b),
                (intersectionPoint.Z - Center.Z) / (c * c)
            ).Normalize();

            return new Intersection(true, true, this, line, t, normal, Material, Color);
        }

    }
}
