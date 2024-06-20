# Fire Shader Project with OpenGL

Video: https://youtu.be/avBwmokHAJo

This project focuses on implementing a fire shader effect using OpenGL, utilizing various image processing techniques and theoretical aspects of image treatment.

## Introduction

OpenGL (Open Graphics Library) is a standard API used for efficient 2D and 3D graphics rendering by leveraging the GPU. It is essential in the development of video games, simulations, scientific visualizations, and general graphical applications.

A key feature of OpenGL is the use of shaders, small programs executed on the GPU to customize and optimize the rendering process. Written in GLSL (OpenGL Shading Language), shaders allow developers precise control over graphics rendering, resembling a syntax similar to C.

There are two main types of shaders:

- **Vertex Shader**: Processes each vertex individually, transforming vertex coordinates and calculating their positions in screen space, enabling complex geometric operations.
  
- **Fragment Shader**: Processes each fragment (or potential pixel), determining the final pixel color and enabling advanced visual effects such as textures, lighting calculations, and more.

## Installation of Libraries

For this project, several libraries were essential for handling images and managing windows in OpenGL:

- **stb_image.h**: Popular single-file image loading library by Sean Barrett, capable of loading most popular image file formats.
  
- **GLFW**: Library specifically aimed at OpenGL, providing basic functionalities such as creating an OpenGL context, defining window parameters, and handling user input.

- **GLAD**: Library for loading OpenGL functions dynamically at runtime, essential as OpenGL function locations are not known at compile time.

The project assumes compilation on Windows with Visual Studio 2022, with pre-compiled libraries included in the project folder.

## Textures

The fire shader requires a special texture containing multiple layers of information encoded in different color channels:

- **Red, Green, and Alpha Channels**: Noise textures used to provide color variations in the fire shader.
  
- **Blue Channel**: Alpha mask defining the area where flames appear.

To combine these textures efficiently into a single file, tools like ImageMagick were used. The command `magick red.png green.png blue.png alpha.png -channel RGBA -combine fire.png` was utilized to merge individual textures into one RGBA image.

## Files

Several essential files were utilized to implement and visualize the fire effect in OpenGL:

- **Shader.h**: Manages shader loading, compilation, linking, and uniform setting in OpenGL.
  
- **Shader.cpp**: Implements the functions declared in Shader.h, handling shader compilation, linking, and error management.
  
- **fire.vs**: Vertex shader responsible for positioning vertices and passing texture coordinates.
  
- **fire.fs**: Fragment shader crucial for achieving the fire visual effect, defining pixel colors based on texture coordinates and elapsed time.

- **Main.cpp**: Entry point of the program, initializing OpenGL, handling user input, and continuously rendering the scene with the fire effect.

Each file plays a specific role in configuring and executing the OpenGL rendering pipeline, ensuring the fire shader effect is rendered effectively.
