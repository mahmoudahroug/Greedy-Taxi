#pragma once
#include "Car.h"
#include "Camera.h"
class Player
{
public:
	Car car;
	Camera camera;
	enum ViewMode { FirstPerson, ThirdPerson };
	ViewMode currentView;
	void init(Vector3 pos, Vector3 s, Vector3 extraS, int angle, char* m);
	void display();
	Vector3 getPosition() { return car.position; };
	float getSpeed() { return car.speed; };
	void update(float deltaTime);
    void accelerate();
	void stopAcceleration();
	void reverse();
	void brake();
	void turnLeft();
	void turnRight();
	void stopTurning();
	void setCollisionNormal(Vector3 normal);
	void firstPerson();
	void thirdPerson();
	void handleMouseButton(int button, int state, int x, int y);
	void handleMouseMotion(int x, int y);
	void toggleViewMode();
	Player() : currentView(ThirdPerson) {}
};

