#include "Chaser.h"
#include <iostream>
#include <cmath>
#include <glut.h>
void Chaser::init(Vector3 pos, Vector3 s, Vector3 extraS, int angle, char* m, Car* chasee) {
	car.init(pos, s, extraS, angle, m);
	this->chasee = chasee;
	car.speed = 20;
}
void Chaser::display() {
	car.render();
}
void Chaser::update(float deltaTime) {
	Vector3 chaseePos = chasee->position;
	Vector3 direction = chaseePos - car.position;
	direction.normalize();
	float angle = atan2(direction.x, direction.z) * 180 / 3.14159f;
	car.speed = 20;
	if (car.angle < angle)
		car.turnLeft();
	else if (car.angle > angle)
		car.turnRight();
	else
		car.stopTurning();
	car.angle = angle;
	car.update(deltaTime);
}
void Chaser::accelerate() {
	car.accelerate();
}
void Chaser::stopAcceleration() {
	car.stopAcceleration();
}
void Chaser::reverse() {
	car.reverse();
}
void Chaser::brake() {
	car.brake();
}
void Chaser::turnLeft() {
	car.turnLeft();
}
void Chaser::turnRight() {
	car.turnRight();
}
void Chaser::stopTurning() {
	car.stopTurning();
}
void Chaser::setCollisionNormal(Vector3 normal) {
	car.setCollisionNormal(normal);
}
