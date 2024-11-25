#include "Car.h"

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
	speed += acceleration;
	if (speed > maxSpeed) {
		speed = maxSpeed;
	}
	if (speed < -maxSpeed) {
		speed = -maxSpeed;
	}
	angle += angularSpeed * deltaTime;
	x += speed * deltaTime;
}

