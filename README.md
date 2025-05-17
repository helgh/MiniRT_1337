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

</body>
</html>
