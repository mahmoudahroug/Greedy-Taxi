#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <Vector3.h>
#include <glut.h>


class Camera {
public:
    static Camera* instance;

private:
    Vector3 eye;      // Camera position
    Vector3 center;  // Look-at point
    double cameraYaw, cameraPitch;     // Camera angles
    double cameraDistance;             // Distance from center point
    int lastMouseX, lastMouseY;        // For mouse movement tracking
    bool preset;                       // Camera preset flag

    void updateEyePosition();

public:
    Camera();
    void setup();
    void handleMouseMotion(int x, int y);
    void handleMouseButton(int button, int state, int x, int y);
    void setView(int view);
};


