#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;
in vec4 exColor;

out vec4 FragmentColor;

void main(void)
{
    vec4 color = (clamp(abs(vec4(normalize(exNormal), 1.0f)), 0.8f, 1.0f) * exColor);
    FragmentColor = color;
}
