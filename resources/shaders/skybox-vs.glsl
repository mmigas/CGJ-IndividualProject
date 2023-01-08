#version 330 core
in vec3 inPosition;

out vec3 texCoords;

uniform Camera {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main() {
    texCoords = inPosition;
    vec4 position = ProjectionMatrix * ViewMatrix * vec4(inPosition, 1.0f);
    gl_Position = position.xyww;
}
