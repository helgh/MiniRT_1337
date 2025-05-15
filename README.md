Project Title
A brief description of what this project does and who it's for

Raytracing: MiniRT Project - README
This document provides a comprehensive guide to implementing a basic raytracer for the MiniRT project. It covers the fundamental concepts, step-by-step implementation, and key mathematical formulations.

1. Introduction to Raytracing
Raytracing is a rendering technique for generating realistic images by simulating the path of light as pixels in an image plane. It traces rays from the camera (eye) through each pixel and calculates how they interact with objects in the scene.

Key Concepts:
Primary Ray: A ray cast from the camera through a pixel into the scene.
Intersection Tests: Determine if a ray hits an object (sphere, plane, cylinder, etc.).
Shading: Compute the color of a pixel based on lighting (diffuse, specular, shadows).
Recursive Reflections/Refractions (Optional): Simulate mirror-like or transparent materials.
2. Steps to Implement Raytracing in MiniRT
Step 1: Define the Scene
The scene consists of:

Camera: Position, orientation, and field of view (FOV).
Light Sources: Ambient, point, or directional lights.
Objects: Spheres, planes, cylinders, etc., each with material properties (color, reflectivity, etc.).
Step 2: Ray Generation
For each pixel (i, j) on the image plane:

Compute the normalized device coordinates (NDC) of the pixel.
Convert NDC to world-space coordinates using the camera’s properties.
Generate a ray from the camera’s position (origin) through the pixel (direction).
Step 3: Ray-Object Intersection
For each object in the scene, compute if the ray intersects it and find the closest hit point.

Sphere Intersection
Given a sphere with center C and radius R:

Solve the quadratic equation:
(P - C)² = R² where P = O + tD (ray equation).
The discriminant determines if there’s an intersection.
Plane Intersection
Given a plane defined by N·P + d = 0:

Substitute the ray equation and solve for t.
Cylinder Intersection (Optional)
More complex; involves solving a quadratic equation in 3D.

Step 4: Shading (Phong Illumination Model)
Compute the color at the intersection point using:

Ambient Light: Base illumination.
Diffuse Reflection: Lambert’s cosine law (N·L).
Specular Reflection: Blinn-Phong model ((N·H)^shininess).
Shadows: Cast a ray to the light; if blocked, the point is in shadow.
Step 5: Output the Image
Store the computed pixel colors in an image file (.ppm format is simplest).

3. Mathematical Foundations
Ray Equation
A ray is defined as:
P(t) = O + tD
where:

O = ray origin (camera position),
D = normalized direction vector,
t = distance along the ray.
Normalizing Vectors
Ensure all direction vectors are normalized (|D| = 1) for correct lighting calculations.

Transformation Matrices (Optional)
If objects are transformed (scaled, rotated), apply inverse transformations to the ray.

4. Optimization Tips
Bounding Volume Hierarchy (BVH): Speed up intersection tests by grouping objects.
Multithreading: Render pixels in parallel for faster execution.
Anti-Aliasing: Average multiple rays per pixel for smoother edges.
5. Example Workflow
Parse the scene file (.rt) to load objects, lights, and camera.
Initialize the image buffer (width × height).
For each pixel:
Generate a primary ray.
Find the closest intersection.
Compute shading.
Store the color.
Write the image to a file (out.ppm).
6. References
Ray Tracing in One Weekend (Peter Shirley)
Scratchapixel - Raytracing
Phong Reflection Model (Wikipedia)
7. Conclusion
This guide covers the essential steps for implementing a basic raytracer for the MiniRT project. Extend it with more objects, textures, or advanced effects (reflections, refractions) for a more sophisticated renderer.

Happy coding! 🚀
