# p3-engine
PICO-8-like pixel game engine

A PICO-8-like 2D game engine supporting both rasterized sprite rendering and modern shaders, created using SDL and OpenGL. The engine provides access to its resource management, audio and rendering functions through a single class passed into _init() _update() and _draw() functions of a single C++ game script. The game script can then be compiled together with the game engine files to create an executable.  

Note: this project is in active development and is unstable. The engine is in the process of being ported from SDL to OpenGL so that GPU-optimized shaders can be used. 
