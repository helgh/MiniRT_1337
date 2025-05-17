# MiniRT - A Minimal Ray Tracer in C

![MiniRT Example Render](https://via.placeholder.com/800x400?text=MiniRT+Sample+Render)

MiniRT is a ray tracing renderer that simulates light physics to generate realistic images of 3D scenes from custom `.rt` configuration files. The project includes both a mandatory implementation with basic features and a bonus implementation with advanced capabilities.

## Table of Contents
- [Features](#features)
- [System Architecture](#system-architecture)
- [Ray Tracing Pipeline](#ray-tracing-pipeline)
- [Data Structures](#data-structures)
- [Primitive Types](#primitive-types)
- [Memory Management](#memory-management)
- [Build System](#build-system)
- [Installation](#installation)
- [Usage](#usage)
- [Scene File Format](#scene-file-format)
- [Contributing](#contributing)
- [License](#license)

## Features

### Mandatory Features
- Basic ray tracing with spheres, planes, and cylinders
- Multiple light sources with shadows
- Camera movement and perspective control
- Scene configuration via `.rt` files

### Bonus Features
- Cone primitive support
- Texture mapping (XPM files)
- Bump mapping effects
- Checkerboard patterns

## System Architecture

MiniRT follows a classic ray tracing architecture:

```mermaid
graph TD
    A[.rt Scene Files] --> B[Scene Parser]
    B --> C[t_scene Data Structure]
    C --> D[Ray Tracing Engine]
    D --> E[MLX Rendering System]
    E --> F[Output Image]
    C --> G[Memory Management]
