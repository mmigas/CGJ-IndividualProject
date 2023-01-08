#include <glm/glm.hpp>
#include <filesystem>

#include "../mgl/mgl.hpp"
#include "Scene.hpp"
#include "../materials/MaterialsLibrary.hpp"
#include "Renderer.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {

public:
    MyApp();

    void initCallback(GLFWwindow *win) override;

    void displayCallback(GLFWwindow *win, double elapsed) override;

    void windowSizeCallback(GLFWwindow *win, int width, int height) override;

    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void scrollCallback(GLFWwindow *win, double xoffset, double yoffset);

private:
    Scene &scene;
    Renderer renderer;

    void drawScene();

};


/////////////////////////////////////////////////////////////////////////// DRAW

void MyApp::drawScene() {
    renderer.drawScene();
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow *win) {
    int width, height;
    glfwGetWindowSize(win, &width, &height);

    renderer.createShaderPrograms();
    MaterialsLibrary::getInstance().createMaterial("default", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, mgl::ShaderType::light);
    scene.init(new mgl::Camera(width, height, glm::vec3(0.0f, 0.0f, -8.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    scene.createEntity("RedSquare.obj", MaterialsLibrary::getInstance().getMaterialID("default"), glm::vec3(0.0f), glm::vec3(90, 0, 0), glm::vec3(1.0f));
    scene.createLight(glm::vec3(0.0f, 0.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
}

void MyApp::windowSizeCallback(GLFWwindow *win, int winx, int winy) {
    glViewport(0, 0, winx, winy);
    scene.getCamera()->resize(winx, winy);
}

void MyApp::displayCallback(GLFWwindow *win, double elapsed) {
    drawScene();
}

void MyApp::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        scene.getCamera()->changeMode();
    }
}

void MyApp::scrollCallback(GLFWwindow *win, double xoffset, double yoffset) {
    scene.getCamera()->updateZoom(yoffset);
}

MyApp::MyApp() : scene(Scene::getInstance()) {

}

/////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char *argv[]) {
    mgl::Engine &engine = mgl::Engine::getInstance();
    engine.setApp(new MyApp());
    engine.setOpenGL(4, 6);
    engine.setWindow(800, 600, "Mesh Loader", 0, 1);
    engine.init();
    engine.run();
    exit(EXIT_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
