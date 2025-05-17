# MiniRT - A Minimal Ray Tracer in C

![MiniRT Banner](https://github.com/helgh/MiniRT_1337/blob/master/Screenshot%20from%202025-05-17%2018-29-59.png)
![MiniRT Banner](https://github.com/helgh/MiniRT_1337/blob/master/Screenshot%20from%202025-05-17%2018-35-26.png)

MiniRT is a C-based ray tracing engine that renders 3D scenes from custom configuration files. It includes both mandatory (basic) and bonus (advanced) implementations.

## Table of Contents
- [Features](#features)
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

## Features

### Mandatory Features
- 🎯 Ray tracing with spheres, planes, and cylinders
- 💡 Multiple light sources with shadows
- 📷 Camera movement and perspective control
- 🖌️ Basic scene rendering

### Bonus Features
- 🔺 Cone primitive support
- 🖼️ Texture mapping (XPM files)
- 🌀 Bump mapping effects
- ♟️ Checkerboard patterns

## System Architecture

```mermaid
graph TD
    A[.rt Scene File] --> B[Scene Parser]
    B --> C[t_scene Structure]
    C --> D[Ray Tracer]
    D --> E[MLX Display]
    C --> F[Memory Manager]

```

| Primitive  | Mandatory | Bonus | Description                          |
|------------|-----------|-------|--------------------------------------|
| Sphere     | ✓         | ✓     | Defined by center and radius         |
| Plane      | ✓         | ✓     | Infinite plane with point and normal |
| Cylinder   | ✓         | ✓     | Defined by center, axis, dimensions  |
| Cone       | ✗         | ✓     | Circular cone with apex angle        |
