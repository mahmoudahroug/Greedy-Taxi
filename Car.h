#pragma once
#define ACCELERATION 0.0005f
#define BRAKE_FORCE 0.0005f
#define ANGULAR_SPEED 0.5f
#include "Vector3.h"
#include "DynamicObject.h"
class Car : public DynamicObject
{
public:
	float angularSpeed;

	void render();
	void update(float deltaTime);
	void accelerate();
	void stopAcceleration();
	void reverse();
	void brake();
	void turnLeft();
	void turnRight();
	void stopTurning();

	Car() : angularSpeed(0) {}
private:
	void rotateY(float rad) {
		// Rotate the direction vector around the Y-axis
		float cosA = cos(rad);
		float sinA = sin(rad);

		float newX = front.x * cosA - front.z * sinA;
		float newZ = front.x * sinA + front.z * cosA;

		front = Vector3(newX, front.y, newZ).normalize();
	}
};

