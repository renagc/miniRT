# miniRT
Ray Tracing

## Rasterization vs Ray Tracing

Rasterization and Ray Tracing are two distinct techniques employed in computer graphics to render 3D scenes into 2D images. Rasterization, commonly used in real-time applications like video games, projects 3D objects onto a 2D plane and determines pixel colors based on simplified shading models. While it offers efficiency for real-time rendering, it may compromise on rendering realism, especially in terms of lighting and shadows.

In contrast, Ray Tracing is a method that closely mimics the behavior of light. It traces rays of light as they interact with objects in a 3D scene, resulting in highly realistic lighting, shadows, and reflections. Although computationally intensive, Ray Tracing is renowned for its ability to produce photorealistic images and is commonly used in movies, high-quality graphics, and offline rendering.

### Main Differences:

| Aspect                    | Rasterization                 | Ray Tracing                   |
|---------------------------|------------------------------|-------------------------------|
| **Light Simulation**      | Simplified shading per pixel | Realistic light ray tracing   |
| **Shadows**               | Often approximated           | Naturally produces shadows    |
| **Global Illumination**   | Limited or approximated      | Supports global illumination  |
| **Examples**              | Video games, real-time       | Movies, high-quality graphics |
| **Efficiency**            | Generally efficient for real-time applications | Computationally intensive, suited for offline rendering and high-quality graphics |

This table summarizes the main differences between rasterization and ray tracing, including their approach to lighting and shadows, support for global illumination, typical use cases, and efficiency considerations.