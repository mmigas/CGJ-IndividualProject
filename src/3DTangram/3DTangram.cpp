////////////////////////////////////////////////////////////////////////////////
//
//  Loading meshes from external files
//
// (c) 2022 by Carlos Martinho
//
// INTRODUCES:
// MODEL DATA, ASSIMP, mglMesh.hpp
//
////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>

#include "../mgl/mgl.hpp"
#include "Scene.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP

struct cursor {
    double xPos, yPos, lastPosX, lastPosY;
};

class MyApp : public mgl::App {

public:
    void initCallback(GLFWwindow *win) override;

    void displayCallback(GLFWwindow *win, double elapsed) override;

    void windowSizeCallback(GLFWwindow *win, int width, int height) override;

    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void scrollCallback(GLFWwindow *win, double xoffset, double yoffset);

private:
    const GLuint UBO_BP = 0;
    GLuint UboId;
    mgl::Camera *camera;
    Scene scene;

    cursor cursor;
    int activeCam = 0;

    void drawScene();

    void createCameras(int width, int height);

    void deleteCameras();

};


///////////////////////////////////////////////////////////////////////// CAMERA

void MyApp::createCameras(int width, int height) {
    glGenBuffers(1, &UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, UboId);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, 0, GL_STREAM_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    camera = new mgl::Camera(width, height, UboId, glm::vec3(0.0f, -8.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void MyApp::deleteCameras() {
    delete camera;
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glDeleteBuffers(1, &UboId);
}


/////////////////////////////////////////////////////////////////////////// DRAW


void MyApp::drawScene() {
    scene.drawScene();
}


////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow *win) {
    scene.buildTangram();
    int width, height;
    glfwGetWindowSize(win, &width, &height);
    createCameras(width, height);
}

void MyApp::windowSizeCallback(GLFWwindow *win, int winx, int winy) {
    glViewport(0, 0, winx, winy);
    camera->resize(winx, winy);
}

void MyApp::displayCallback(GLFWwindow *win, double elapsed) {
    drawScene();
}

void MyApp::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        camera->changeMode();
    }

    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        activeCam = activeCam == 0 ? 1 : 0;
        std::cout << activeCam << std::endl;
        camera->updateMatrices();
    }
}

void MyApp::scrollCallback(GLFWwindow *win, double xoffset, double yoffset) {
    camera->updateZoom(yoffset);
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
