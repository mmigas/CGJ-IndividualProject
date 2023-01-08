#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

layout (std140) uniform Material {
    vec3 color;
    vec3 diffuse;
    vec3 specular;
} material;

out vec4 FragmentColor;

void main(void) {
    FragmentColor = vec4(material.color, 1.0f);
}
