#include <glm/glm.hpp>

#include "../mgl/mgl.hpp"
#include "Scene.hpp"
#include "../materials/MaterialsLibrary.hpp"
#include "Renderer.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP
struct cursor {
    double xPos = 0;
    double yPos = 0;
    double lastXPos = 0;
    double lastYPos = 0;
    bool pressing = false;
};

class MyApp : public mgl::App {

public:
    MyApp();

    void initCallback(GLFWwindow *win) override;

    void displayCallback(GLFWwindow *win, double elapsed) override;

    void windowSizeCallback(GLFWwindow *win, int width, int height) override;

    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void scrollCallback(GLFWwindow *win, double xoffset, double yoffset) override;

    void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) override;

private:
    Scene &scene;
    Renderer renderer;
    cursor cursor;

    void drawScene();

    //temporary
    void updateCamera();
};


/////////////////////////////////////////////////////////////////////////// DRAW

void MyApp::drawScene() {
    renderer.draw();
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow *win) {
    int width, height;
    glfwGetWindowSize(win, &width, &height);
    renderer.init();
    renderer.loadSkyBox("resources/textures/skybox/sky");
    renderer.createShaderPrograms();
    MaterialsLibrary::getInstance().createMaterial("default", glm::vec3(1.0f, 1.0f, 1.0f), 32.0f, 0.0f, mgl::ShaderType::unlit);
    scene.init(new mgl::Camera(width, height, glm::vec3(0.0f, 0.0f, -8.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    scene.createEntity("RedSquare.obj", MaterialsLibrary::getInstance().getMaterialID("default"), glm::vec3(0.0f), glm::vec3(90, 0, 0), glm::vec3(1.0f));
    scene.createLight(glm::vec3(0.0f, 0.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
}

void MyApp::windowSizeCallback(GLFWwindow *win, int winx, int winy) {
    glViewport(0, 0, winx, winy);
    scene.getCamera()->resize(winx, winy);
}

void MyApp::displayCallback(GLFWwindow *win, double elapsed) {
    glfwGetCursorPos(win, &cursor.xPos, &cursor.yPos);
    if (cursor.pressing) {
        updateCamera();
    }
    drawScene();
}

void MyApp::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        scene.getCamera()->changeMode();
    }

}

void MyApp::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_3) {
        if (action == GLFW_PRESS) {
            cursor.pressing = true;
            cursor.lastXPos = cursor.xPos;
            cursor.lastYPos = cursor.yPos;
        } else if (action == GLFW_RELEASE) {
            cursor.pressing = false;
        }
    }
}

void MyApp::updateCamera() {
    mgl::Camera *cam1 = Scene::getInstance().getCamera();
    glm::vec4 position(cam1->GetEye().x, cam1->GetEye().y, cam1->GetEye().z, 1);
    glm::vec4 pivot(cam1->GetLookAt().x, cam1->GetLookAt().y, cam1->GetLookAt().z, 1);

    // step 1 : Calculate the amount of rotation given the mouse movement.
    float deltaAngleX = (2 * glm::pi<float>() / cam1->GetWidth()); // a movement from left to right = 2*PI = 360 deg
    float deltaAngleY = (glm::pi<float>() / cam1->GetHeight());  // a movement from top to bottom = PI = 180 deg
    float xAngle = (cursor.lastXPos - cursor.xPos) * deltaAngleX;
    float yAngle = (cursor.lastYPos - cursor.yPos) * deltaAngleY;

    // Extra step to handle the problem when the camera direction is the same as the up vector
    float cosAngle = dot(cam1->GetViewDir(), cam1->GetUpVector());
    if (cosAngle * glm::sign(yAngle) > 0.99f)
        yAngle = 0;

    // step 2: Rotate the camera around the pivot point on the first axis.
    glm::mat4x4 rotationMatrixX(1.0f);
    rotationMatrixX = glm::rotate(rotationMatrixX, xAngle, cam1->GetUpVector());
    position = (rotationMatrixX * (position - pivot)) + pivot;

    // step 3: Rotate the camera around the pivot point on the second axis.
    glm::mat4x4 rotationMatrixY(1.0f);
    rotationMatrixY = glm::rotate(rotationMatrixY, yAngle, cam1->GetRightVector());
    glm::vec3 finalPosition = (rotationMatrixY * (position - pivot)) + pivot;

    // Update the camera view (we keep the same lookat and the same up vector)
    cam1->setCameraView(finalPosition, cam1->GetLookAt(), cam1->GetUpVector());

    // Update the mouse position for the next rotation
    cursor.lastXPos = cursor.xPos;
    cursor.lastYPos = cursor.yPos;
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
