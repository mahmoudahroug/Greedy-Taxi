#include "Car.h"
#include <cmath>

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
	if (speed < -maxSpeed) {
		speed = -maxSpeed;
	}

	angle += angularSpeed * deltaTime;
	float rad = angle * 3.14159f / 180.0f;
	rotateY(rad);
	velocity = front * speed;
	position = position + velocity * deltaTime;

}

