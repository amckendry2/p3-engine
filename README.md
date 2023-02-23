# p3-engine
A PICO-8-like 2D game engine created using SDL and OpenGL. The engine provides access to its resource management, audio and rendering functions through a single class passed into _init() _update() and _draw() functions of a single C++ game script. The game script can then be compiled together with the game engine files to create an executable.  

Note: this project is in active development and is unstable. I am in the process of migrating some rendering functions to OpenGL so that GPU-optimized shaders can be used. 
