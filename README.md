The Bull renderer is a OpenGL project with the ability to render different objects with specific materials that can reflect and interact with light.
***

## Getting Started

The Bull renderer is a cmake project and clion was used to develop this project.

<ins>**Clion:**</ins>

1. Open the project folder
2. In Settings>Build,Execution,Deploy>Toolchains change to Visual Studio 2022 with x64 architecture.
3. In Settings>Build,Execution,Deploy>Cmake change the tool chain to Visual Studio and generator to Visual studio as well.
4. Press play to run

<ins>**Visual Studio:**</ins>

1. Open project using open local folder option in the launch configurator
2. Select Debug or Release configuration and x64.
3. Press play to run

***

## Usage

There are multiple default scenes available to showcase different aspects of the program.
To change between them go to:

1. File>Open
3. Choose one .scene file from the folder

The camera is orbital that can be moved by dragging the mouse while holding middle button.
It's possible to zoom in an out by scrolling with the middle button.

In the scene hierarchy its possible to select different objects that can be moved around using the gizmos.

***

## Dependencies and Resources

All dependencies are installed using cmake.
Dependencies used:

1. GLEW
2. glfw
3. assimp
4. glm
5. imgui
6. imguizmo
7. stb_image
8. yaml-cpp

In resources the project loads.

1. The objects models
2. Scenes folder
3. Shaders
4. Skybox textures
