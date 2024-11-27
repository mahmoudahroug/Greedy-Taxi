#pragma once
#define ACCELERATION 2
#define BRAKE_FORCE 2
#define ANGULAR_SPEED 30
#include <iostream>
#include "Vector3.h"
#include "DynamicObject.h"
class Car : public DynamicObject
{
public:
	float angularSpeed;
	bool braking = false; 
	void render();
	void update(float deltaTime);
	void accelerate();
	void stopAcceleration();
	void reverse();
	void brake();
	void turnLeft();
	void turnRight();
	void stopTurning();
	void drawVectors();
	Car() : angularSpeed(0) {
		maxSpeed = 5;
		size = Vector3(2, 2, 5);
	}
private:
	void rotate(float rad) {
		float cosA = cos(rad);
		float sinA = sin(rad);
		//float newX = front.x * cosA - front.z * sinA;
		//float newZ = front.x * sinA + front.z * cosA;

		// front -> (sinA, 0, cosA) (no y component / incline)
		front = Vector3(sinA, front.y, cosA);
		right = Vector3(front.z, front.y, -front.x);
		// for incline
		// cosB = cos (pitch); sinB = sin(pitch)
		// front -> (cosB sinA, sinB , cosB cosA)
	}
};

