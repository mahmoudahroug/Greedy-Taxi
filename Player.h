#pragma once
#include "Car.h"
#include "Camera.h"
class Player : public DynamicObject
{
public:
	Car car;
	Camera camera;

	void init(Vector3 pos, Vector3 s, int angle, char* m);
	void display();
	void update(float deltaTime);
    void accelerate();
	void stopAcceleration();
	void reverse();
	void brake();
	void turnLeft();
	void turnRight();
	void stopTurning();
	void firstPerson();
	void thirdPerson();
	void handleMouseButton(int button, int state, int x, int y);
	void handleMouseMotion(int x, int y);
};

