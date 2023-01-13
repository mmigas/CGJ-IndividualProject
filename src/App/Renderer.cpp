#include "Renderer.hpp"

Renderer::Renderer() : scene(Scene::getInstance()) {

}

void Renderer::init() {
    skybox.init();
    glGenBuffers(1, &materialsUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, materialsUBO);
    glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4) + 2 * sizeof(float) + sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, mgl::MATERIAL_BLOCK_BINDING_POINT, materialsUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Renderer::createShaderPrograms() {
    createShaderProgram(mgl::ShaderType::unlit, "resources/shaders/unlit-vs.glsl", "resources/shaders/unlit-fs.glsl");
    createShaderProgram(mgl::ShaderType::light, "resources/shaders/light-vs.glsl", "resources/shaders/light-fs.glsl");
    createSkyBoxShaderProgram("resources/shaders/skybox-vs.glsl", "resources/shaders/skybox-fs.glsl");
}

void Renderer::loadSkyBox(const std::string &skyboxFolder) {
    skybox.loadCubeMap(skyboxFolder);
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
    shaders->addUniform(mgl::CAMERA_POSITION);
    shaders->addUniform(mgl::SKYBOX);
    shaders->addUniformBlock(mgl::CAMERA_BLOCK, mgl::CAMERA_BLOCK_BINDING_POINT);
    shaders->addUniformBlock(mgl::MATERIAL_BLOCK, mgl::MATERIAL_BLOCK_BINDING_POINT);
    shaders->addUniformBlock(mgl::LIGHT_BLOCK, mgl::LIGHT_BLOCK_BINDING_POINT);
    shaders->create();
    shaderPrograms.insert(std::make_pair(shaderType, shaders));
}

void Renderer::createSkyBoxShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    mgl::ShaderProgram *shaders = new mgl::ShaderProgram();
    shaders->addShader(GL_VERTEX_SHADER, vertexShaderPath);
    shaders->addShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
    shaders->addUniform(mgl::SKYBOX);
    shaders->addUniformBlock(mgl::CAMERA_BLOCK, mgl::CAMERA_BLOCK_BINDING_POINT);
    shaders->create();
    shaderPrograms.insert(std::make_pair(mgl::ShaderType::skybox, shaders));
}

void Renderer::draw() {
    drawScene();
    drawSkyBox();
}

void Renderer::drawObject(std::shared_ptr<Object> object) {
    std::shared_ptr<mgl::ShaderProgram> shader = shaderPrograms[object->getMaterial()->getShaderType()];
    shader->bind();
    if (object->getMaterial()->getShaderType() == mgl::ShaderType::light) {
        scene.getLight()->bind();
    }
    glm::vec3 cameraPosition = Scene::getInstance().getCamera()->GetEye();
    glUniform3f(shader->Uniforms[mgl::CAMERA_POSITION].index, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform1i(shader->Uniforms[mgl::SKYBOX].index, 0);
    glUniformMatrix4fv(shader->Uniforms[mgl::MODEL_MATRIX].index, 1, GL_FALSE, glm::value_ptr(object->getModelMatrix()));
    object->draw(materialsUBO);
    shader->unbind();
}

void Renderer::drawChildren(std::shared_ptr<Object> parent) {
    for (std::shared_ptr<Object> child: parent->getChildren()) {
        drawChildren(child);
    }
    drawObject(parent);
}

void Renderer::drawScene() {
    for (std::shared_ptr<Object> object: scene.getObjects()) {
        drawChildren(object);
        drawObject(object);
    }
}

void Renderer::drawSkyBox() {
    glDepthFunc(GL_LEQUAL);
    std::shared_ptr<mgl::ShaderProgram> shader = shaderPrograms[mgl::ShaderType::skybox];
    glm::mat4 viewMatrixBackUp = Scene::getInstance().getCamera()->GetViewMatrix();
    Scene::getInstance().getCamera()->setViewMatrix(glm::mat4(glm::mat3(Scene::getInstance().getCamera()->GetViewMatrix())));
    shader->bind();
    glUniform1i(shader->Uniforms[mgl::SKYBOX].index, 0);
    skybox.draw();
    shader->unbind();
    Scene::getInstance().getCamera()->setViewMatrix(viewMatrixBackUp);
    glDepthFunc(GL_LESS);
}

