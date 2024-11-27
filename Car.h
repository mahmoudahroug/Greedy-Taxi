#pragma once
#define ACCELERATION 0.000001f
#define BRAKE_FORCE 0.000001f
#define ANGULAR_SPEED 0.05f
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
		maxSpeed = 0.01f;
		size = Vector3(2, 2, 5);
	}
private:
	void rotateY(float rad) {
		// Rotate the direction vector around the Y-axis
		float cosA = cos(rad);
		float sinA = sin(rad);
		//float newX = front.x * cosA - front.z * sinA;
		//float newZ = front.x * sinA + front.z * cosA;

		front = Vector3(sinA, front.y, cosA);
	}
};

