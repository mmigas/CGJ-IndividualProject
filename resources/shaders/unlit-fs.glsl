#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

uniform vec3 CameraPosition;
uniform samplerCube Skybox;

uniform Material {
    vec3 color;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float reflectiveness;
} material;

out vec4 FragmentColor;

void main(void) {
    vec3 normal = normalize(exNormal);

    vec3 I = normalize(exPosition - CameraPosition);
    vec3 R = reflect(I, normal);
    vec3 result = mix(material.color, texture(Skybox, R).rgb, material.reflectiveness);
    FragmentColor = vec4(result, 1.0f);
}
