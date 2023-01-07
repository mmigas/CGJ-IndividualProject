#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

uniform Material {
    vec3 color;
    vec3 diffuse;
    vec4 specular;
    float shininess;
};

out vec4 FragmentColor;

void main(void)
{
    FragmentColor = vec4(color, 1.0f);
}
