#include "Renderer.hpp"

Renderer::Renderer() : scene(Scene::getInstance()) {

}

void Renderer::createShaderPrograms() {
    createShaderProgram(mgl::ShaderType::unlit, "resources/shaders/unlit-vs.glsl", "resources/shaders/unlit-fs.glsl");
    createShaderProgram(mgl::ShaderType::light, "resources/shaders/light-vs.glsl", "resources/shaders/light-fs.glsl");
}

void Renderer::createShaderProgram(mgl::ShaderType shaderType, const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    mgl::ShaderProgram *shaders = new mgl::ShaderProgram();
    shaders->addShader(GL_VERTEX_SHADER, vertexShaderPath);
    shaders->addShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

    shaders->addAttribute(mgl::POSITION_ATTRIBUTE, mgl::Mesh::POSITION);
    shaders->addAttribute(mgl::NORMAL_ATTRIBUTE, mgl::Mesh::NORMAL);
    shaders->addAttribute(mgl::TEXCOORD_ATTRIBUTE, mgl::Mesh::TEXCOORD);
    shaders->addAttribute(mgl::TANGENT_ATTRIBUTE, mgl::Mesh::TANGENT);

    shaders->addUniform(mgl::MODEL_MATRIX);
    if (shaderType == mgl::ShaderType::light) {
        shaders->addUniform(mgl::CAMERA_POSITION);
    }
    shaders->addUniformBlock(mgl::CAMERA_BLOCK, mgl::CAMERA_BLOCK_BINDING_POINT);
    shaders->addUniformBlock(mgl::MATERIAL_BLOCK, mgl::MATERIAL_BLOCK_BINDING_POINT);
    shaders->addUniformBlock(mgl::LIGHT_BLOCK, mgl::LIGHT_BLOCK_BINDING_POINT);
    shaders->create();
    shaderPrograms.insert(std::make_pair(shaderType, shaders));
}

void Renderer::drawScene() {
    for (Object &object: scene.getObject()) {
        std::shared_ptr<mgl::ShaderProgram> shader = shaderPrograms[object.getMaterial()->getShaderType()];
        shader->bind();
        if (object.getMaterial()->getShaderType() == mgl::ShaderType::light) {
            scene.getLight()->bind();
            glm::vec3 cameraPosition = Scene::getInstance().getCamera()->GetEye();
            glUniform3f(shader->Uniforms[mgl::CAMERA_POSITION].index, cameraPosition.x, cameraPosition.y, cameraPosition.z);
        }
        object.draw();
        shader->unbind();
    }
}
