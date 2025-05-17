<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MiniRT - A Ray Tracing Engine</title>
    <style>
        :root {
            --primary: #3498db;
            --secondary: #2ecc71;
            --dark: #2c3e50;
            --light: #ecf0f1;
            --danger: #e74c3c;
        }
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: #333;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f9f9f9;
        }
        h1, h2, h3, h4 {
            color: var(--dark);
            margin-top: 1.5em;
        }
        h1 {
            border-bottom: 2px solid var(--primary);
            padding-bottom: 10px;
        }
        h2 {
            border-left: 4px solid var(--primary);
            padding-left: 10px;
        }
        code {
            background-color: #f0f0f0;
            padding: 2px 5px;
            border-radius: 3px;
            font-family: 'Courier New', monospace;
        }
        pre {
            background-color: #f0f0f0;
            padding: 15px;
            border-radius: 5px;
            overflow-x: auto;
            border-left: 3px solid var(--primary);
        }
        .container {
            background-color: white;
            border-radius: 8px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            padding: 25px;
            margin-bottom: 30px;
        }
        .badge {
            display: inline-block;
            padding: 3px 8px;
            font-size: 12px;
            font-weight: bold;
            border-radius: 20px;
            margin-right: 5px;
        }
        .badge-mandatory {
            background-color: var(--primary);
            color: white;
        }
        .badge-bonus {
            background-color: var(--secondary);
            color: white;
        }
        .badge-core {
            background-color: var(--dark);
            color: white;
        }
        .architecture-diagram {
            width: 100%;
            max-width: 800px;
            margin: 20px auto;
            display: block;
        }
        .data-structure {
            background-color: #f8f9fa;
            border: 1px solid #dee2e6;
            border-radius: 5px;
            padding: 15px;
            margin: 15px 0;
        }
        .data-structure h4 {
            margin-top: 0;
            color: var(--primary);
        }
        .tabs {
            display: flex;
            border-bottom: 1px solid #ddd;
            margin-bottom: 20px;
        }
        .tab-btn {
            padding: 10px 20px;
            background: none;
            border: none;
            cursor: pointer;
            font-weight: bold;
            color: #666;
            border-bottom: 3px solid transparent;
        }
        .tab-btn.active {
            color: var(--primary);
            border-bottom: 3px solid var(--primary);
        }
        .tab-content {
            display: none;
        }
        .tab-content.active {
            display: block;
        }
        .gallery {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
            gap: 20px;
            margin: 20px 0;
        }
        .gallery img {
            width: 100%;
            border-radius: 5px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
            transition: transform 0.3s;
        }
        .gallery img:hover {
            transform: scale(1.02);
        }
        .primitive-table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }
        .primitive-table th, .primitive-table td {
            border: 1px solid #ddd;
            padding: 12px;
            text-align: left;
        }
        .primitive-table th {
            background-color: var(--primary);
            color: white;
        }
        .primitive-table tr:nth-child(even) {
            background-color: #f2f2f2;
        }
        .flow-diagram {
            background-color: white;
            padding: 20px;
            border-radius: 5px;
            margin: 20px 0;
            border: 1px solid #ddd;
        }
        .flow-step {
            margin-bottom: 15px;
            padding-left: 20px;
            position: relative;
        }
        .flow-step:before {
            content: "→";
            position: absolute;
            left: 0;
            color: var(--primary);
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>MiniRT - A Minimal Ray Tracer</h1>
        
        <div class="tabs">
            <button class="tab-btn active" onclick="openTab(event, 'overview')">Overview</button>
            <button class="tab-btn" onclick="openTab(event, 'architecture')">Architecture</button>
            <button class="tab-btn" onclick="openTab(event, 'primitives')">Primitives</button>
            <button class="tab-btn" onclick="openTab(event, 'usage')">Usage</button>
            <button class="tab-btn" onclick="openTab(event, 'gallery')">Gallery</button>
        </div>
        
        <div id="overview" class="tab-content active">
            <h2>What is MiniRT?</h2>
            <p>MiniRT is a ray tracing renderer that simulates light physics to generate realistic images of 3D scenes. The project includes both a mandatory implementation with basic features and a bonus implementation that adds advanced capabilities such as textures, bump mapping, and additional primitive types.</p>
            
            <h3>Key Features</h3>
            <ul>
                <li>Basic ray tracing with spheres, planes, and cylinders</li>
                <li>Multiple light sources with shadows</li>
                <li>Camera movement and perspective</li>
                <li>Scene configuration via custom .rt files</li>
                <li>Bonus features: cones, textures, bump mapping</li>
                <li>Custom memory management system</li>
            </ul>
            
            <h3>Core Components</h3>
            <div class="data-structure">
                <h4>t_scene - Central Data Structure</h4>
                <p>Holds all scene elements and rendering state:</p>
                <ul>
                    <li>Camera position and orientation</li>
                    <li>Light sources</li>
                    <li>Geometric primitives (spheres, planes, cylinders, cones)</li>
                    <li>Ambient lighting</li>
                    <li>Memory management references</li>
                    <li>MLX rendering context</li>
                </ul>
            </div>
        </div>
        
        <div id="architecture" class="tab-content">
            <h2>System Architecture</h2>
            <p>MiniRT follows a classic ray tracing architecture with these major components:</p>
            
            <div class="flow-diagram">
                <div class="flow-step">Scene Description (.rt files)</div>
                <div class="flow-step">Scene Parser</div>
                <div class="flow-step">Scene Data Structure (t_scene)</div>
                <div class="flow-step">Ray Tracing Engine</div>
                <div class="flow-step">MLX Rendering System</div>
                <div class="flow-step">Output Image</div>
            </div>
            
            <h3>Ray Tracing Pipeline</h3>
            <div class="flow-diagram">
                <div class="flow-step">Camera</div>
                <div class="flow-step">Ray Generation</div>
                <div class="flow-step">Intersection Testing</div>
                <div class="flow-step">Closest Hit Determination</div>
                <div class="flow-step">Normal Calculation</div>
                <div class="flow-step">Shadow Testing</div>
                <div class="flow-step">Lighting Calculation</div>
                <div class="flow-step">Color Determination</div>
                <div class="flow-step">Pixel Rendering</div>
            </div>
            
            <h3>Memory Management</h3>
            <p>MiniRT uses a custom memory management system to track and free all allocated memory:</p>
            <pre><code>// Example memory management functions
void *ft_malloc(size_t size);      // Allocate and track memory
void __ft_free(void);              // Free all allocated memory
void print_scene_err(char *msg);   // Error handling with memory cleanup</code></pre>
        </div>
        
        <div id="primitives" class="tab-content">
            <h2>Supported Primitive Types</h2>
            
            <table class="primitive-table">
                <thead>
                    <tr>
                        <th>Primitive</th>
                        <th>Mandatory</th>
                        <th>Bonus</th>
                        <th>Description</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td>Sphere</td>
                        <td>✓</td>
                        <td>✓</td>
                        <td>Simple sphere defined by center position and radius</td>
                    </tr>
                    <tr>
                        <td>Plane</td>
                        <td>✓</td>
                        <td>✓</td>
                        <td>Infinite plane defined by point and normal vector</td>
                    </tr>
                    <tr>
                        <td>Cylinder</td>
                        <td>✓</td>
                        <td>✓</td>
                        <td>Cylinder defined by center, axis, radius, and height</td>
                    </tr>
                    <tr>
                        <td>Cone</td>
                        <td></td>
                        <td>✓</td>
                        <td>Cone defined by center, axis, radius, and height</td>
                    </tr>
                </tbody>
            </table>
            
            <h3>Bonus Features</h3>
            <ul>
                <li>Texture mapping (using XPM files)</li>
                <li>Checkerboard patterns</li>
                <li>Bump mapping for surface details</li>
                <li>Additional geometric primitives</li>
            </ul>
            
            <h3>Scene File Format Example</h3>
            <pre><code>R 1920 1080            # Resolution
A 0.2 255,255,255     # Ambient light
C 0,0,5 0,0,0 70      # Camera (position, orientation, FOV)
L -10,10,10 0.8 255,255,255  # Light (position, brightness, color)
sp 0,0,0 2 255,0,0    # Sphere (center, radius, color)
pl 0,0,0 0,1,0 128,128,128  # Plane (point, normal, color)
cy 0,0,0 0,1,0 1 3 0,0,255   # Cylinder (center, axis, radius, height, color)</code></pre>
        </div>
        
        <div id="usage" class="tab-content">
            <h2>Building and Usage</h2>
            
            <h3>Build System</h3>
            <p>MiniRT uses a Makefile to manage compilation:</p>
            <pre><code># Build mandatory version
make

# Build bonus version
make bonus

# Clean build files
make clean

# Clean everything
make fclean</code></pre>
            
            <h3>Running MiniRT</h3>
            <p>Invoke MiniRT with a scene file as argument:</p>
            <pre><code># Mandatory version
./miniRT scenes/basic.rt

# Bonus version
./miniRT_bonus scenes/advanced.rt</code></pre>
            
            <h3>Controls</h3>
            <ul>
                <li><strong>WASD</strong>: Move camera</li>
                <li><strong>Arrow keys</strong>: Rotate camera</li>
                <li><strong>ESC</strong>: Quit program</li>
                <li><strong>Space</strong>: Toggle bonus features (if available)</li>
            </ul>
            
            <h3>System Initialization</h3>
            <div class="flow-diagram">
                <div class="flow-step">Initialize MLX window</div>
                <div class="flow-step">Parse scene file</div>
                <div class="flow-step">Build scene data structure</div>
                <div class="flow-step">Render scene</div>
                <div class="flow-step">Display result</div>
            </div>
        </div>
        
        <div id="gallery" class="tab-content">
            <h2>Gallery</h2>
            <div class="gallery">
                <!-- Replace with your actual images -->
                <div>
                    <h3>Basic Scene</h3>
                    <img src="https://via.placeholder.com/400x300?text=Sphere+and+Plane" alt="Basic Scene">
                </div>
                <div>
                    <h3>Multiple Objects</h3>
                    <img src="https://via.placeholder.com/400x300?text=Multiple+Primitives" alt="Multiple Objects">
                </div>
                <div>
                    <h3>Bonus Features</h3>
                    <img src="https://via.placeholder.com/400x300?text=Textures+and+Bump+Mapping" alt="Bonus Features">
                </div>
            </div>
        </div>
        
        <h2>Contributing</h2>
        <p>Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.</p>
        
        <h2>License</h2>
        <p>This project is licensed under the MIT License - see the <a href="LICENSE">LICENSE</a> file for details.</p>
    </div>
    
    <script>
        function openTab(evt, tabName) {
            // Hide all tab contents
            const tabContents = document.getElementsByClassName("tab-content");
            for (let i = 0; i < tabContents.length; i++) {
                tabContents[i].classList.remove("active");
            }
            
            // Remove active class from all tab buttons
            const tabButtons = document.getElementsByClassName("tab-btn");
            for (let i = 0; i < tabButtons.length; i++) {
                tabButtons[i].classList.remove("active");
            }
            
            // Show the current tab and mark button as active
            document.getElementById(tabName).classList.add("active");
            evt.currentTarget.classList.add("active");
        }
        
        // Add interactivity to data structures
        document.addEventListener('DOMContentLoaded', function() {
            // You can add more interactive elements here
            console.log("MiniRT README loaded");
        });
    </script>
</body>
</html>
