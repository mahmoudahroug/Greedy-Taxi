#pragma once
#define ACCELERATION 10
#define BRAKE_FORCE 10
#define ANGULAR_SPEED 1
#include <iostream>
#include "Vector3.h"
#include "DynamicObject.h"
#include <string>
class Car : public DynamicObject
{
public:
	
	float angularSpeed;
	bool braking = false; 

	void update(float deltaTime);
	void updateHeadlights();
	void accelerate();
	void stopAcceleration();
	void reverse();
	void brake();
	void turnLeft();
	void turnRight();
	void stopTurning();
	void drawVectors();
	void setCollisionNormal(Vector3 normal);
	//void init(Vector3 pos, Vector3 s,int angle, char* m);
	//Car(Vector3 pos, Vector3 s, Model_3DS* m) : angularSpeed(0) {
	//	DynamicObject(pos, s, m);
	//	maxSpeed = 5;
	//	size = Vector3(2, 2, 5);
	//}
	Car():angularSpeed(0){
		maxSpeed = 100;
		collisionNormal = Vector3(0, 0, 0);
		headlightOffsetLeft = Vector3(-0.5f, 0.0f, 1.0f);
		headlightOffsetRight = Vector3(0.5f, 0.0f, 1.0f);
	}
private:
	//bool collided = false;
	Vector3 collisionNormal;
	void handleCollision();
	Vector3 headlightOffsetLeft;
	Vector3 headlightOffsetRight;
};

