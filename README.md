# vulkan-tutorial
This is a simple study project that follows the 
[Vulkan Implementation Tutorial](https://vulkan-tutorial.com/). 
The idea here is to solely
document the process and make it easier for me to further
reference the code inside the tutorial. 
The end goal, however, is to be able to implement Vulkan on my 
[Ottocento Renderer Raytracer](https://github.com/lknknm/ottocento-renderer), another study project I am currently 
developing with a much bigger scope.

I will be following the tutorial but will also make changes that suit my personal code style as well as
some other needs I will have to learn in the long run and want to implement on other projects. 
For this reason, the code on this project won't be a 100% copy of the original code from the Vulkan Tutorial.
If you want to see the original code, please reference it on the `References` section.

### What is Vulkan?
> Vulkan is a new API by the Khronos group (known for OpenGL) that provides a much better 
abstraction of modern graphics cards. This new interface allows you to better describe what your 
application intends to do, which can lead to better performance and less surprising driver behavior 
compared to existing APIs like OpenGL and Direct3D. The ideas behind Vulkan are similar to those of 
Direct3D 12 and Metal, but Vulkan has the advantage of being fully cross-platform and allows you to develop 
for Windows, 
Linux and Android at the same time.

### Steps / "Roadmap" 
- [x] Setting up Development Environment.
- [x] Instance Creation.
- [x] Validation Layers Implementation.
- [x] Physical Devices and Queue Families selection.
- [x] Logical device and queues.
- [x] Window Surface creation.
- [x] Swap Chain
- [x] Image Views
- [x] Graphics Pipeline Basics
  - [x] Shader Modules
  - [x] Fixed Functions
  - [x] Render Passes
- [x] Frame buffers
- [x] Command Buffers
- [x] Rendering and Presentation (finally rendering the first triangle)
- [x] Frames in flight
- [x] Swap Chain Recreation

### Additional (not covered inside the tutorial)
- [x] Setting up Development Environment with Premake5.lua for Windows and Linux.
- [x] UI: Win32 Dark Titlebar to follow the Darkmode from the system.
- [x] GLFW: Change the Window Icon (further can be expanded to be a call to the GPU to decode a Hex Array).

### References
- [Vulkan Tutorial](https://vulkan-tutorial.com/)
- [Vulkanised 2024: Common Mistakes When Learning Vulkan - Charles Giessen](https://www.youtube.com/watch?v=0OqJtPnkfC8)
- [Rasterizer Algorithm Explanation](https://www.youtube.com/watch?v=t7Ztio8cwqM)
- [Homogeneous Coordinates](https://en.wikipedia.org/wiki/Homogeneous_coordinates)