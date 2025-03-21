# Ottocento Engine

![screenshot_sandoy_model.jpg](resource/models/screenshot_sandoy_model.jpg)
> Model: á Sondum, Sandoy. Faroe Islands National Museum. Model by Helgi D. Michelsen. License CC0.

Ottocento Engine is a non-commercial, personal project I started after following the vulkan-tutorial to understand graphics programming
in a deeper level. I am an architect and urban planner myself, so naturally I wanted to engage in building an architectural BIM
engine to study computer graphics. 

Ever since I started using architectural software — probably more than 10 years ago — I have been a critic on how some of them
operate, so I decided to understand how they work under the hood in a much more deeper level. This is why I am using
Vulkan to learn about graphics programming. It is known to be hard and verbose, but the reward factor is much higher compared to the
efforts, and I so far am not aware of any other architectural BIM software that is being built from the absolute zero that uses it.

The software is so far very in it's early stages, but it's being born with the a few concepts I want to follow in the long-run:

- BIM and Archviz could and should be integrated.
- Different stages of designing buildings, drafting, modelling and documenting a project should be integrated smoothly throughout the whole process.
- Tools and features should be integrated at no cost of money and performance to the end user, much like Blender integrates new features within it and keeps it concise.

### What is Vulkan?
> Vulkan is a new API by the Khronos group (known for OpenGL) that provides a much better 
abstraction of modern graphics cards. This new interface allows you to better describe what your 
application intends to do, which can lead to better performance and less surprising driver behavior 
compared to existing APIs like OpenGL and Direct3D. The ideas behind Vulkan are similar to those of 
Direct3D 12 and Metal, but Vulkan has the advantage of being fully cross-platform and allows you to develop 
for Windows, 
Linux and Android at the same time.
> 

### Documentation

- To see how to build the project, please refer to the [Build Guide](./doc/build.md)
- To see how we style our code, please refer to the [Code Style Guide](./doc/styleguide.md).
- To see the list of resources used to construct this project, please refer to [References/Resources](./doc/resources.md)

### License
Ottocento Engine is licensed under the GNU General Public License, Version 3.
See License