# MiniRT - A Minimal Ray Tracer in C

![MiniRT Banner](https://github.com/helgh/MiniRT_1337/blob/master/Screenshot%20from%202025-05-17%2018-29-59.png)
![MiniRT Banner](https://github.com/helgh/MiniRT_1337/blob/master/Screenshot%20from%202025-05-17%2018-35-26.png)

MiniRT is a C-based ray tracing engine that renders 3D scenes from custom configuration files. It includes both mandatory (basic) and bonus (advanced) implementations.

## Table of Contents
- [Overview](#Overview)
- [System Architecture](#system-architecture)
- [Ray Tracing Pipeline](#ray-tracing-pipeline)
- [Core Data Structures](#core-data-structures)
- [Primitive Types](#primitive-types)
- [Memory Management](#memory-management)
- [Build System](#build-system)
- [Installation](#installation)
- [Usage](#usage)
- [Scene File Format](#scene-file-format)
- [Controls](#controls)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

### Overview
This document provides a high-level overview of MiniRT, a ray tracing engine implemented in C that renders 3D scenes described in a custom .rt file format. For specific details about the scene file format, see [System Architecture](#system-architecture).

#### -^- What is MiniRT?
MiniRT is a ray tracing renderer that simulates light physics to generate realistic images of 3D scenes. The project includes both a mandatory implementation with basic features and a bonus implementation that adds advanced capabilities such as textures, bump mapping, and additional primitive types.

#### -^- System Architecture

```mermaid
graph TD
    B["Scene Description<br><small>(.rt files)</small>"] --> C["Scene Parser"]
    C --> D["Scene Data Structure<br><small>(t_scene)</small>"]
    D --> E["Ray Tracing Engine"]
    E --> F["MLX Rendering System"]
    F --> G["Output Image"]
    A["Memory Management<br> System"] --> C
    A --> D
    A --> E
    A --> F
```

**Each component has a specific responsibility:**
    - **Scene Parser**: Reads `.rt` files and creates scene objects
    - **Scene Data Structure**: Central data repository for all scene information  
    - **Ray Tracing Engine**: Performs ray-object intersections and lighting calculations
    - **MLX Rendering System**: Displays the final rendered image
    - **Memory Management**: Handles allocation and cleanup of resources

#### -^- Ray Tracing Pipeline
**The core rendering process follows this pipeline:**


| Primitive  | Mandatory | Bonus | Description                          |
|------------|-----------|-------|--------------------------------------|
| Sphere     | ✓         | ✓     | Defined by center and radius         |
| Plane      | ✓         | ✓     | Infinite plane with point and normal |
| Cylinder   | ✓         | ✓     | Defined by center, axis, dimensions  |
| Cone       | ✗         | ✓     | Circular cone with apex angle        |
