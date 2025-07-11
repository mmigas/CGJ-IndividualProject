#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;

uniform mat4 ModelMatrix;

uniform Camera {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main(void) {
    exPosition = vec3(ModelMatrix * vec4(inPosition, 1.0f));;
    exTexcoord = inTexcoord;
    exNormal = mat3(transpose(inverse(ModelMatrix))) * inNormal;

    vec4 MCPosition = vec4(inPosition, 1.0);
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
}
