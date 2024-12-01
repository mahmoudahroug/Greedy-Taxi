#include "Car.h"
#include <iostream>
#include <cmath>
#include <glut.h>

void Car::accelerate() { 
	acceleration = ACCELERATION;
	
}
void Car::stopAcceleration() {
	acceleration = 0;
}
void Car::reverse() {
	acceleration = -ACCELERATION;
}
void Car::brake() {
	acceleration = -BRAKE_FORCE;
}
void Car::turnLeft() {
	angularSpeed = ANGULAR_SPEED;

}
void Car::turnRight() {
	angularSpeed = -ANGULAR_SPEED;

}
void Car::stopTurning() {
	angularSpeed = 0;
}
void Car::update(float deltaTime) {
	
	speed += acceleration * deltaTime;
	if (speed > maxSpeed) {
		speed = maxSpeed;
	}
	if (speed < 0) {
		speed = 0;
	}

	angle += angularSpeed * speed * deltaTime;
	if (angle > 360) {
		angle -= 360;
	}
	float rad = angle * 3.14159f / 180.0f;
	
	rotate(rad);
	if (collisionNormal != Vector3(0, 0, 0))
		handleCollision();
	velocity = front * speed;
	position = position + velocity * deltaTime;

}


void drawVector(float x, float y, float z) {
	GLUquadric* quadric = gluNewQuadric();

	float length = sqrt(x * x + y * y + z * z); // Calculate vector length
	float angle = acos(z / length) * 180.0 / 3.141592f; // Angle for rotation
	float axisX = -y, axisY = x; // Rotation axis (perpendicular to the vector)

	// Save current transformation
	glPushMatrix();

	// Position and rotate cylinder
	glTranslatef(0.0f, 0.0f, 0.0f); // Start at the origin
	glRotatef(angle, axisX, axisY, 0.0f);

	// Draw cylinder (vector body)
	gluCylinder(quadric, 0.05, 0.05, length, 20, 20);

	// Draw cone (arrowhead) at the end of the cylinder
	glTranslatef(0.0f, 0.0f, length); // Move to cylinder's end
	glutSolidCone(0.1, 0.2, 20, 20);

	// Restore transformation
	glPopMatrix();

	gluDeleteQuadric(quadric); // Clean up
}
void Car::drawVectors() {
	// Draw velocity vector
	glColor3f(1, 0, 0); // Red
	drawVector(velocity.x, velocity.y, velocity.z);

	// Draw acceleration vector
	//glColor3f(0, 1, 0); // Green
	//drawVector(accelerationVector.x, accelerationVector.y, accelerationVector.z);

	//glColor3f(0, 0, 1); // Blue
	//drawVector(front.x, front.y, front.z);
}
void Car::handleCollision() {
	// Reflect velocity vector off the collision normal
	if (velocity == Vector3(0, 0, 0)) {
		return;
	}
	Vector3 recoil = collisionNormal * velocity.dot(collisionNormal);
	velocity = velocity - recoil + collisionNormal;
	front = velocity.normalize();
	right = front.cross(Vector3(0, 1, 0));
	angle = atan2(front.x, front.z) * 180.0 / 3.141592f;
	collisionNormal = Vector3(0, 0, 0);
}
void Car::setCollisionNormal(Vector3 normal) {
	collisionNormal = normal;
}