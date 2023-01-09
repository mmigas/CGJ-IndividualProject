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
    bool transparent;
} material;

out vec4 FragmentColor;

void main(void) {
    vec3 normal = normalize(exNormal);

    //Environment reflection
    vec3 I = normalize(exPosition - CameraPosition);
    vec3 R = reflect(I, normal);
    vec3 reflectionColor = texture(Skybox, R).rgb;

    vec3 reflectionMatColor = mix(material.color, reflectionColor, material.reflectiveness);

    vec3 finalColor;
    if (material.transparent) {
        //Environment refraction
        float ratio = 1.0f / 1.52f; //Air to glass
        vec3 N = refract(I, normal, ratio);
        vec3 refractionColor = texture(Skybox, N).rgb;
        finalColor = mix(refractionColor, reflectionMatColor, 0.5f);
    } else {
        finalColor = reflectionMatColor;
    }

    FragmentColor = vec4(finalColor, 1.0f);
}
