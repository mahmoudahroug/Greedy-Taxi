#include "Camera.h"
Camera* Camera::instance = nullptr; 

Camera::Camera()
    : eye(10, 5, 10),
    center(0,3.0,0),
    cameraYaw(0.0), cameraPitch(0.0), cameraDistance(10.0),
    lastMouseX(0), lastMouseY(0), preset(false) {
}

void Camera::updateEyePosition() {
    if (!preset) {
        eye.x = center.x + cameraDistance * cos(cameraPitch) * sin(cameraYaw);
        eye.y = center.y + cameraDistance * sin(cameraPitch);
        eye.z = center.z + cameraDistance * cos(cameraPitch) * cos(cameraYaw);
    }
}

void Camera::setup() {
    updateEyePosition();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, 640.0 / 480.0, 0.001, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, 0, 1, 0);
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
        preset = false;
        lastMouseX = x;
        lastMouseY = y;
        glutMotionFunc([](int x, int y) { instance->handleMouseMotion(x, y); });
    }
    else {
        glutMotionFunc(nullptr); // Unregister motion callback
    }
}

void Camera::setView(int view) {
    switch (view) {
    case 1: // Top View
        cameraYaw = 0.0;
        cameraPitch = M_PI_2;
        cameraDistance = 10.0;
        center.x = center.y = center.z = 0.0;
        break;
    case 2: // Front View
        cameraYaw = 0.0;
        cameraPitch = 0.0;
        cameraDistance = 10.0;
        center.x = center.z = 0.0;
        center.y = 3.0;
        break;
    case 3: // Side View
        cameraYaw = -M_PI_2;
        cameraPitch = 0.0;
        cameraDistance = 10.0;
        center.x = center.z = 0.0;
        center.y = 3.0;
        break;
    case 4: center.z -= 0.2; break;
    case 5: center.z += 0.2; break;
    case 6: center.x -= 0.2; break;
    case 7: center.x += 0.2; break;
    case 8: center.y += 0.2; break;
    case 9: center.y -= 0.2; break;
    }
    updateEyePosition();
    glutPostRedisplay();  // Redraw scene
}