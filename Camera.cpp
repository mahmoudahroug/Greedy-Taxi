#include "Camera.h"
Camera* Camera::instance = nullptr; 
Camera::Camera()
    : eye(10, 5, 10),
    center(0,3.0,0),
    cameraYaw(0.0), cameraPitch(0.5), cameraDistance(5.0),
    lastMouseX(0), lastMouseY(0), preset(false) {
}

void Camera::updateEyePosition(Vector3 position, float cameraYaw) {
    if (preset) {
		cameraDistance = 1.0;
    }
    else {
        cameraDistance = 5.0;
    }
    eye.x = position.x + cameraDistance * cos(cameraPitch) * sin(cameraYaw * M_PI / 180 +M_PI);
    eye.y = position.y + cameraDistance * sin(cameraPitch);
    eye.z = position.z + cameraDistance * cos(cameraPitch) * cos(cameraYaw * M_PI / 180 +M_PI);
    
}

void Camera::setup(Vector3 position, float cameraYaw, Vector3 front) {
    updateEyePosition(position, cameraYaw);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, 1280.0 / 720.0, 0.1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (preset) {
		front = front * 1.5;
        gluLookAt(eye.x + front.x, eye.y + front.y + 0.4, eye.z + front.z, position.x + front.x, position.y + front.y, position.z + front.z, 0, 1, 0);
    }
	else
    gluLookAt(eye.x, eye.y, eye.z, position.x, position.y, position.z, 0, 1, 0);
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
        glutMotionFunc([](int x, int y) { instance->handleMouseMotion(x, y); });
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
