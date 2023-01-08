#version 330 core
in vec3 texCoords;

out vec4 FragmentColor;

uniform samplerCube Skybox;

void main()
{
    FragmentColor = texture(Skybox, texCoords);
}