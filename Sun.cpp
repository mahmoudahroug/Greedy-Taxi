#include "Sun.h"

Sun::Sun(float initialAngle, float speed) : angle(initialAngle), cycleSpeed(speed) {
    // Default light colors
    ambientColor[0] = 0.2f; ambientColor[1] = 0.2f; ambientColor[2] = 0.2f; ambientColor[3] = 1.0f;
    diffuseColor[0] = 1.0f; diffuseColor[1] = 1.0f; diffuseColor[2] = 1.0f; diffuseColor[3] = 1.0f;
    specularColor[0] = 1.0f; specularColor[1] = 1.0f; specularColor[2] = 1.0f; specularColor[3] = 1.0f;

    position = Vector3(0.0f, 10.0f, 0.0f);
}

// Update the sun's position and light properties
void Sun::update(float deltaTime) {
    // Increment the angle based on the cycle speed and delta time
    angle += cycleSpeed * deltaTime;
    if (angle > 360.0f) {
        angle -= 360.0f; // Keep the angle in [0, 360]
    }

    // Compute the sun's position in the sky (circular path)
    float radians = angle * 3.14159f / 180.0f;
    position.x = 10.0f * cos(radians);  // Circular x-component
    position.y = 10.0f * sin(radians);  // Circular y-component

    // Update light properties based on the angle
    updateLightProperties();
}

// Update light properties (color and intensity) based on the sun's angle
void Sun::updateLightProperties() {
    if (angle >= 0 && angle < 90) { // Sunrise
        ambientColor[0] = 0.8f; ambientColor[1] = 0.5f; ambientColor[2] = 0.3f;
        diffuseColor[0] = 1.0f; diffuseColor[1] = 0.7f; diffuseColor[2] = 0.5f;
    }
    else if (angle >= 90 && angle < 180) { // Daytime
        ambientColor[0] = 0.3f; ambientColor[1] = 0.3f; ambientColor[2] = 0.3f;
        diffuseColor[0] = 1.0f; diffuseColor[1] = 1.0f; diffuseColor[2] = 1.0f;
    }
    else if (angle >= 180 && angle < 270) { // Sunset
        ambientColor[0] = 0.8f; ambientColor[1] = 0.4f; ambientColor[2] = 0.2f;
        diffuseColor[0] = 1.0f; diffuseColor[1] = 0.5f; diffuseColor[2] = 0.3f;
    }
    else { // Night
        ambientColor[0] = 0.1f; ambientColor[1] = 0.1f; ambientColor[2] = 0.2f;
        diffuseColor[0] = 0.2f; diffuseColor[1] = 0.2f; diffuseColor[2] = 0.3f;
    }

    // Ensure alpha remains 1.0
    ambientColor[3] = diffuseColor[3] = specularColor[3] = 1.0f;
}

// Apply the light settings to OpenGL
void Sun::applyLight() {
    GLfloat lightPosition[] = { position.x, position.y, position.z, 1.0f };
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
}