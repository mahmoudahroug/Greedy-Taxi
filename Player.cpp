#include "Player.h"

void Player::init(Vector3 pos, Vector3 s, int angle, char* m)
{
	camera.setup(car.position, car.angle, car.front);
	car.init(pos, s, angle, m);
}
void Player::display()
{
	car.render();
	camera.setup(car.position, car.angle, car.front);
}
void Player::update(float deltaTime)
{
	car.update(deltaTime);
}
void Player::accelerate()
{
	car.accelerate();
}
void Player::stopAcceleration()
{
	car.stopAcceleration();
}
void Player::reverse()
{
	car.reverse();
}
void Player::brake()
{
	car.brake();
}
void Player::turnLeft()
{
	car.turnLeft();
}
void Player::turnRight()
{
	car.turnRight();
}
void Player::stopTurning()
{
	car.stopTurning();
}
void Player::firstPerson()
{
	camera.carFirstPerson();
}
void Player::thirdPerson()
{
	camera.carThirdPerson();
}

void Player::handleMouseButton(int button, int state, int x, int y)
{
	camera.handleMouseButton(button, state, x, y);
}
void Player::handleMouseMotion(int x, int y)
{
	camera.handleMouseMotion(x, y);
}
