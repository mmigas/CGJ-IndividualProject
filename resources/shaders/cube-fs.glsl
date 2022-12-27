#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;
in vec4 exColor;

out vec4 FragmentColor;

void main(void)
{
    FragmentColor = vec4(1.0f,1.0f,1.0f,1.0f);
}
