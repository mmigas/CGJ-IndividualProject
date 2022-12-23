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
    mgl::Camera *cams[2];
    Scene scene;

    cursor cursor;
    int activeCam = 0;

    void drawScene();

    void createCameras(int width, int height);

    void deleteCameras();

    void updateCamera();
};


///////////////////////////////////////////////////////////////////////// CAMERA

void MyApp::createCameras(int width, int height) {
    glGenBuffers(1, &UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, UboId);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, 0, GL_STREAM_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    cams[0] = new mgl::Camera(width, height, UboId, glm::vec3(0.0f, -8.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    cams[1] = new mgl::Camera(width, height, UboId, glm::vec3(0.45f, 5.7f, 8.0f), glm::vec3(0.45f, 5.7f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void MyApp::deleteCameras() {
    delete cams[0];
    delete cams[1];
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glDeleteBuffers(1, &UboId);
}


/////////////////////////////////////////////////////////////////////////// DRAW


void MyApp::drawScene() {
    scene.drawScene();
}

void MyApp::updateCamera() {
    mgl::Camera *cam1 = cams[activeCam];
    glm::vec4 position(cam1->GetEye().x, cam1->GetEye().y, cam1->GetEye().z, 1);
    glm::vec4 pivot(cam1->GetLookAt().x, cam1->GetLookAt().y, cam1->GetLookAt().z, 1);

    // step 1 : Calculate the amount of rotation given the mouse movement.
    float deltaAngleX = (2 * glm::pi<float>() / cam1->GetWidth()); // a movement from left to right = 2*PI = 360 deg
    float deltaAngleY = (glm::pi<float>() / cam1->GetHeight());  // a movement from top to bottom = PI = 180 deg
    float xAngle = (cursor.lastPosX - cursor.xPos) * deltaAngleX;
    float yAngle = (cursor.lastPosY - cursor.yPos) * deltaAngleY;

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
    cam1->SetCameraView(finalPosition, cam1->GetLookAt(), cam1->GetUpVector());

    // Update the mouse position for the next rotation
    cursor.lastPosX = cursor.xPos;
    cursor.lastPosY = cursor.yPos;

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
    cams[activeCam]->resize(winx, winy);
}

void MyApp::displayCallback(GLFWwindow *win, double elapsed) {
    glfwGetCursorPos(win, &cursor.xPos, &cursor.yPos);
    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS) scene.updatePieces(-1);
    else if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS) scene.updatePieces(1);
    updateCamera();
    drawScene();
}

void MyApp::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        cams[activeCam]->changeMode();
    }

    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        activeCam = activeCam == 0 ? 1 : 0;
        std::cout << activeCam << std::endl;
        cams[activeCam]->updateMatrices();
    }
}

void MyApp::scrollCallback(GLFWwindow *win, double xoffset, double yoffset) {
    mgl::Camera *actCam = cams[activeCam];
    actCam->updateZoom(yoffset);
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
