#include "Camera.h"
Camera* Camera::instance = nullptr; 
Camera* Camera::instance1 = nullptr; 
Camera::Camera()
    : eye(10, 5, 10),
    center(0,3.0,0),
    cameraYaw(0.0), cameraPitch(0.5), cameraDistance(5.0),
    lastMouseX(0), lastMouseY(0), preset(false),currentView(ThirdPerson) {
}

void Camera::updateEyePosition(Vector3 position, float cameraYaw, Vector3 front) {
    if (preset) {
		cameraDistance = 1.0;
    }
    else {
        cameraDistance = 5.0;
    }
    eye.x = position.x + cameraDistance * cos(cameraPitch) * sin(cameraYaw * M_PI / 180 +M_PI);
    eye.y = position.y + cameraDistance * sin(cameraPitch);
    eye.z = position.z + cameraDistance * cos(cameraPitch) * cos(cameraYaw * M_PI / 180 +M_PI);

    if (preset) {
        front = front * 1.5;
        gluLookAt(eye.x + front.x, eye.y + front.y + 0.4, eye.z + front.z, position.x + front.x, position.y + front.y, position.z + front.z, 0, 1, 0);
    }
    else
        gluLookAt(eye.x, eye.y, eye.z, position.x, position.y, position.z, 0, 1, 0);
    
}

void Camera::setup(Vector3 position, float cameraYaw, Vector3 front) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, 1280.0 / 720.0, 0.1, 2000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //std::cout << "PitchBefore: " << cameraPitch << "\n";
    updateEyePosition(position, cameraYaw, front);
    //std::cout << "PitchAfter: " << cameraPitch << "\n";
}

void Camera::handleMouseMotion(int x, int y) {
    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;

    cameraYaw += deltaX * -0.005;   // Adjust sensitivity
    cameraPitch += deltaY * 0.005;

    if (cameraPitch > 1.5) cameraPitch = 1.5; // Prevent flipping
    if (cameraPitch < -1.5) cameraPitch = -1.5;
    lastMouseX = x;
    lastMouseY = y;
    glutPostRedisplay();  // Redraw the scene with the updated camera
}

void Camera::handleMouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
        
		//this->handleMouseMotion(x, y);
        glutMotionFunc([](int x, int y) { instance->handleMouseMotion(x, y); instance1->handleMouseMotion(x, y); });
    }
    else  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        toggleViewMode();
    }
    else {
        glutMotionFunc(nullptr); // Unregister motion callback
    }
}

void Camera::carFirstPerson() {
    preset = true;
}

void Camera::carThirdPerson() {
    preset = false;
}
void Camera::toggleViewMode() {
    if (currentView == FirstPerson) {
        carThirdPerson();
        currentView = ThirdPerson;
    }
    else {
        carFirstPerson();
        currentView = FirstPerson;
    }
}