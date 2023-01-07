#include <glm/glm.hpp>
#include <filesystem>

#include "../mgl/mgl.hpp"
#include "Scene.hpp"
#include "../materials/MaterialsLibrary.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {

public:
    void initCallback(GLFWwindow *win) override;

    void displayCallback(GLFWwindow *win, double elapsed) override;

    void windowSizeCallback(GLFWwindow *win, int width, int height) override;

    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void scrollCallback(GLFWwindow *win, double xoffset, double yoffset);

private:
    Scene scene;

    void drawScene();

};


/////////////////////////////////////////////////////////////////////////// DRAW

void MyApp::drawScene() {
    scene.drawScene();
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow *win) {
    int width, height;
    glfwGetWindowSize(win, &width, &height);

    MaterialsLibrary::getInstance().createMaterial("default", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), mgl::ShaderType::unlit);
    scene.init(new mgl::Camera(width, height, glm::vec3(0.0f, -8.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    scene.createEntity("RedSquare.obj", MaterialsLibrary::getInstance().getMaterialID("default"));
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
