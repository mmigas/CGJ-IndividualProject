cmake_minimum_required(VERSION 3.24)
project(IndividualProject)

# READ THIS
# This document is commented to help you set up your cmake to correctly interpret libs in windows.
# This assumes you know how to setup projects with cmake or use Clion.

# Make sure you use the Visual Studio toolchains and Generator.
# The generator will be named "Visual Studio 16 2019" or "Visual Studio 17 2022".

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DDEBUG)
# Include the OpenGL Package
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
###############################
# RPATH correct path for libs
set(CMAKE_INSTALL_RPATH "lib")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

###############################
# Define output directories

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release")

if (WIN32) # WINDOWS
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release")


    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
    set(LIBRARY_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
endif ()

# Define the libraries you want to include.
# The `add_library` allows you to include libraries to your work.
# The IMPORTED parameter defines the library as an external inclusion
# The SHARED parameter defines the library as a dynamic library (.dll)
add_library(yaml-cpp SHARED IMPORTED)
add_library(GLEW SHARED IMPORTED)
add_library(GLFW SHARED IMPORTED)
add_library(Assimp SHARED IMPORTED)
add_library(imgui STATIC IMPORTED)
add_library(imguizmo STATIC IMPORTED)
# ... add other libs ...

if (WIN32) # WINDOWS
    # Tell CMake where to find the `.dll` and `.lib` file of the library
    set_target_properties(GLEW PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/bin/Release/x64/glew32.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/lib/Release/x64/glew32.lib
            )

    set_target_properties(GLFW PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/lib-vc2022/glfw3.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/lib-vc2022/glfw3dll.lib
            )

    set_target_properties(Assimp PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Assimp/bin/assimp-vc143-mtd.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Assimp/lib/assimp-vc143-mtd.lib
            )

    set_target_properties(imgui PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/lib/imgui.lib
            )

    set_target_properties(imguizmo PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imguizmo/lib/imGuizmo.lib
            )

    set_target_properties(yaml-cpp PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/yaml-cpp/bin/yaml-cppd.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/yaml-cpp/lib/yaml-cppd.lib
            )

    # ... add other libs ...
else ()
    # Define the properties for other OSes
endif ()

# To make it easier, we can create a variable holding all needed lib dependencies
set(GRAPHIC_LIBRARIES
        GLFW
        GLEW
        Assimp
        imgui
        imguizmo
        yaml-cpp
        ${OPENGL_LIBS}
        )


add_executable(${PROJECT_NAME} src/mgl/mgl.hpp
        src/mgl/mglApp.cpp
        src/mgl/mglApp.hpp
        src/mgl/mglCamera.cpp
        src/mgl/mglCamera.hpp
        src/mgl/mglConventions.hpp
        src/mgl/mglError.cpp
        src/mgl/mglError.hpp
        src/mgl/mglMesh.cpp
        src/mgl/mglMesh.hpp
        src/mgl/mglShader.cpp
        src/mgl/mglShader.hpp
        src/App/Application.cpp
        src/scene/Scene.cpp
        src/scene/Scene.hpp
        src/scene/entities/Object.cpp
        src/scene/entities/Object.hpp
        src/scene/entities/Entity.cpp
        src/scene/entities/Entity.hpp
        src/materials/Material.cpp
        src/materials/Material.hpp
        src/materials/MaterialsLibrary.cpp
        src/materials/MaterialsLibrary.hpp
        src/light/Light.cpp
        src/light/Light.hpp
        src/renderer/Renderer.cpp
        src/renderer/Renderer.hpp
        src/textures/SkyBox.cpp
        src/textures/SkyBox.hpp
        src/gui/GuiManager.cpp
        src/gui/GuiManager.hpp
        src/gui/SceneHierarchy.cpp
        src/gui/SceneHierarchy.hpp
        src/gui/Guizmo.cpp
        src/gui/Guizmo.hpp
        src/scene/SceneSerializer.cpp
        src/scene/SceneSerializer.hpp
        src/gui/RendererPanel.cpp
        src/gui/RendererPanel.hpp
        src/renderer/FrameBuffer.cpp
        src/renderer/FrameBuffer.hpp)

include_directories(
        ${OPENGL_INCLUDE_DIRS}
        # Include the `.h` files into your code.
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/include
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/include
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/include
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Assimp/include
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb_image/include
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/include
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imguizmo/include
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/yaml-cpp/include
        # ... add other libs ...
)
# Link the libs with the executable
target_link_libraries(${PROJECT_NAME}
        ${GRAPHIC_LIBRARIES})

add_custom_target(CopyLibs
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} -E echo Copying Dependencies files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/bin/Release/x64/ ${LIBRARY_OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/lib-vc2022/ ${LIBRARY_OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Assimp/bin/assimp-vc143-mtd.dll ${LIBRARY_OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/yaml-cpp/bin/yaml-cppd.dll ${LIBRARY_OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/ini/imgui.ini ${LIBRARY_OUTPUT_PATH}
        )

add_custom_target(CopyResourcesFiles
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} -E echo Copying Resources files
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${EXECUTABLE_OUTPUT_PATH}/resources/
        )

add_dependencies(${PROJECT_NAME} CopyLibs CopyResourcesFiles)
