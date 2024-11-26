#pragma once
#include "Vector3.h"
#include "GameObject.h"
class DynamicObject : public GameObject
{
public:
	Vector3 velocity; // Velocity of object
	float speed; 
	const float maxSpeed;

	Vector3 accelerationVector; // Acceleration vector of object
	float acceleration;
	float gravity;
};

