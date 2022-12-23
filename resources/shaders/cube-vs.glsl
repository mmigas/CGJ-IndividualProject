#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;
in vec4 inColor;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;
out vec4 exColor;

uniform mat4 ModelMatrix;

uniform Camera {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main(void)
{
    exPosition = inPosition;
    exTexcoord = inTexcoord;
    exNormal = inNormal;
    exColor = inColor;

    vec4 MCPosition = vec4(inPosition, 1.0);
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
}
