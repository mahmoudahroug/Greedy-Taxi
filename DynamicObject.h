#pragma once
#include "Vector3.h"
#include "GameObject.h"
class DynamicObject : public GameObject
{
public:
	Vector3 velocity; // Velocity of object
	float speed; 
	float maxSpeed;

	Vector3 accelerationVector; // Acceleration vector of object
	float acceleration;
	float gravity;

	DynamicObject() : maxSpeed(0.1f) {
		velocity = Vector3(0, 0, 0);
		speed = 0;
		accelerationVector = Vector3(0, 0, 0);
		acceleration = 0;
		gravity = 0;
	}
};

