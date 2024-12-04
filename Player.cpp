#include "Player.h"

void Player::init(Vector3 pos, Vector3 s, Vector3 extraS, int angle, char* m)
{
	car.init(pos, s, extraS, angle, m);
	camera.setup(car.position, car.angle, car.front);
}
void Player::display()
{
	car.render();
	
}
void Player::update(float deltaTime)
{
	
	car.update(deltaTime);
	camera.setup(car.position, car.angle, car.front);
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
void Player::setCollisionNormal(Vector3 normal)
{
	car.setCollisionNormal(normal);
}