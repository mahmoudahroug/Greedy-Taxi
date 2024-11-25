#pragma once
#define ACCELERATION 0.0005f
#define BRAKE_FORCE 0.0005f
#define ANGULAR_SPEED 0.5f
class Car
{
public:
	float x, y, z;
	float angle;

	float gravity;

	float speed;
	const float maxSpeed;
	float acceleration;
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

};

