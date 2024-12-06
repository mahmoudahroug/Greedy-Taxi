#pragma once
#include "Car.h"
class Chaser
{
public:
	Car car;
	Car* chasee;
	void init(Vector3 pos, Vector3 s, Vector3 extraS, int angle, char* m, Car* chasee);
	void display();
	Vector3 getPosition() { return car.position; };
	float getSpeed() { return car.speed; };
	float getAngle() { return car.angle; };
	void update(float deltaTime);
	void accelerate();
	void stopAcceleration();
	void reverse();
	void brake();
	void turnLeft();
	void turnRight();
	void stopTurning();
	void setCollisionNormal(Vector3 normal);
};

