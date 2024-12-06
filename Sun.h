#pragma once
#include "Vector3.h"
#include <glut.h>
#define ORBIT_RADIUS 100.0f

class Sun
{
private:
    Vector3 position;       // Current position of the sun
    float angle;            // Current angle (in degrees) for the day-night cycle
    float cycleSpeed;       // Speed of the cycle (degrees per second)

    GLfloat ambientColor[4];
    GLfloat diffuseColor[4];
    GLfloat specularColor[4];

    void updateLightProperties();

public:
    Sun(float initialAngle = 0.0f, float speed = 0.1f);
    void update(float deltaTime);                      // Update position and light properties
    void applyLight();
};

