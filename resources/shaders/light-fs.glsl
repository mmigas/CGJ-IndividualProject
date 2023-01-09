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
} material;

uniform Light {
    vec3 position;
    vec3 color;
    vec3 diffuse;
    vec3 specular;
} light;

out vec4 FragmentColor;

void main(void) {
    // ambient
    vec3 ambient = light.color * material.color;

    // diffuse
    vec3 normal = normalize(exNormal);
    vec3 lightDirection = normalize(light.position - exPosition);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(CameraPosition - exPosition);
    vec3 reflectDir = reflect(-lightDirection, normal);
    vec3 halfwayDir = normalize(lightDirection + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 materialColor = ambient + diffuse + specular;

    vec3 I = normalize(exPosition - CameraPosition);
    vec3 R = reflect(I, normal);

    vec3 result = mix(materialColor, texture(Skybox, R).rgb, 0.0f);

    FragmentColor = vec4(result, 1.0f);
}
