#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "Vector3.h"
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
    bool preset;                 
    // Camera preset flag



public:
    Camera();
    void setup(Vector3 position, float cameraYaw, Vector3 front);
    void updateEyePosition(Vector3 position, float cameraYaw);
    void handleMouseMotion(int x, int y);
    void handleMouseButton(int button, int state, int x, int y);
	void carFirstPerson();
    void carThirdPerson();
};


