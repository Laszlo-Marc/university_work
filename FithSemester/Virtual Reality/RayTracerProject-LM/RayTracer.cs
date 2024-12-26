using System;

namespace rt
{
    class RayTracer
    {
        private Geometry[] geometries;
        private Light[] lights;

        public RayTracer(Geometry[] geometries, Light[] lights)
        {
            this.geometries = geometries;
            this.lights = lights;
        }

        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize)
        {
            var u = n * viewPlaneSize / imgSize;
            u -= viewPlaneSize / 2;
            return u;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist)
        {
            var intersection = new Intersection();

            foreach (var geometry in geometries)
            {
                var intr = geometry.GetIntersection(ray, minDist, maxDist);

                if (!intr.Valid || !intr.Visible) continue;

                if (!intersection.Valid || !intersection.Visible)
                {
                    intersection = intr;
                }
                else if(intr.T < intersection.T)
                {
                    intersection = intr;
                }
            }

            return intersection;
        }
        
        private bool IsLit(Vector point, Light light)
        {
            // Minimum distance to consider for light-ray intersection (to avoid self-intersection issues)
            const double minimumDistance = 0.1;

            // Create a ray from the point to the light's position
            var rayToLight = new Line(point, light.Position);

            // Calculate the distance between the point and the light source
            var distanceToLight = (light.Position - point).Length();

            
            foreach (var geometry in geometries)
            {
                // Skip RawCtMask 
                if (geometry is RawCtMask) continue;

                // Check if the geometry intersects the ray to the light within the valid distance range
                var intersection = geometry.GetIntersection(rayToLight, minimumDistance, distanceToLight);

                // If the geometry intersects the ray and is visible, it blocks the light
                if (intersection.Visible)
                {
                    return false; // The point is not directly illuminated by the light
                }
            }

            // If no geometry blocks the light, the point is illuminated
            return true;

        }
        public void Render(Camera camera, int imageWidth, int imageHeight, string outputFilename, double scaleFactor = 1.0)
        {
            // Background color for pixels where no geometry is intersected
            var backgroundColor = new Color(0.2, 0.2, 0.2, 1.0);

            // Precompute the center of the view plane relative to the camera's position
            var viewPlaneCenter = camera.Position + camera.Direction * camera.ViewPlaneDistance;

            // Compute the right-hand direction vector on the view plane
            var viewPlaneRight = (camera.Up ^ camera.Direction).Normalize(); // Cross product to find perpendicular vector

            // Create an empty image with the specified dimensions
            var image = new Image(imageWidth, imageHeight);

            // Iterate over each pixel in the image grid
            for (var xPixel = 0; xPixel < imageWidth; xPixel++)
            {
                // Calculate the horizontal offset on the view plane for this pixel
                var horizontalOffset = ImageToViewPlane(xPixel, imageWidth, camera.ViewPlaneWidth);

                for (var yPixel = 0; yPixel < imageHeight; yPixel++)
                {
                    // Calculate the vertical offset on the view plane for this pixel
                    var verticalOffset = ImageToViewPlane(yPixel, imageHeight, camera.ViewPlaneHeight);

                    // Compute the direction of the ray from the camera through this pixel
                    var pixelViewDirection = viewPlaneCenter + viewPlaneRight * horizontalOffset + camera.Up * verticalOffset;

                    // Create a ray from the camera's position to the computed direction
                    var rayThroughPixel = new Line(camera.Position, pixelViewDirection);

                    // Find the first intersection of this ray with any scene geometry
                    var closestIntersection = FindFirstIntersection(rayThroughPixel, camera.FrontPlaneDistance, camera.BackPlaneDistance);

                    if (!closestIntersection.Visible)
                    {
                        // If no geometry is intersected, set the pixel to the background color
                        image.SetPixel(xPixel, yPixel, backgroundColor);
                        continue;
                    }

                    // If an intersection is found, compute the pixel color based on lighting and material properties
                    var pixelColor = new Color(); 
                    var intersectionPoint = closestIntersection.Position; // The point of intersection
                    var viewDirection = (camera.Position - intersectionPoint).Normalize(); // Vector from the intersection point to the camera
                    var surfaceNormal = closestIntersection.Normal; // Surface normal at the intersection point
                    var material = closestIntersection.Material; 

                    
                    foreach (var lightSource in lights)
                    {
                        // Initialize the color contribution from this light source
                        var lightContribution = material.Ambient * lightSource.Ambient; // Ambient lighting contribution

                        
                        if (IsLit(intersectionPoint, lightSource))
                        {
                            // Compute the vector from the intersection point to the light source
                            var lightDirection = (lightSource.Position - intersectionPoint).Normalize();

                            // Compute the reflection direction of the light on the surface
                            var reflectionDirection = (surfaceNormal * (surfaceNormal * lightDirection) * 2 - lightDirection).Normalize();

                            // Calculate the diffuse lighting contribution (based on angle between light and surface normal)
                            var diffuseFactor = surfaceNormal * lightDirection; 
                            if (diffuseFactor > 0)
                            {
                                lightContribution += material.Diffuse * lightSource.Diffuse * diffuseFactor;
                            }

                            // Calculate the specular lighting contribution (based on angle of reflection and view direction)
                            var specularFactor = viewDirection * reflectionDirection; 
                            if (specularFactor > 0)
                            {
                                lightContribution += material.Specular * lightSource.Specular * Math.Pow(specularFactor, material.Shininess);
                            }

                            // Scale the total light contribution by the light's intensity
                            lightContribution *= lightSource.Intensity;
                        }

                        
                        pixelColor += lightContribution;
                    }

                    
                    image.SetPixel(xPixel, yPixel, pixelColor);
                }
            }

            image.Store(outputFilename);
        }


       

    }

}
