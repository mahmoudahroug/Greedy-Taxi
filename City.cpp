#include "City.h"

void City::display() {
	player.display();
	glPushMatrix();
	glScaled(0.4, 0.4, 0.4);
	model_city.Draw();
	glPopMatrix();
	//model_taxi.Draw();
}

void City::init() {
	player.init(Vector3(-1, 0.1, 1.5), Vector3(1, 1, 2.3), Vector3(0.2, 0.2, 0.2), 180, "models/city_taxi/Taxi.3ds");
	Camera::instance = &player.camera;
	engine1 = createIrrKlangDevice();
	if (!engine1) {
		std::cerr << "Sound engine could not start." << std::endl;
	}
}

void City::LoadAssets()
{
	// Loading Model files
	model_city.Load("models/city/city.3ds");
	//model_taxi.Load("models/city_taxi/Taxi.3ds");
}

void City::keyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': player.stopAcceleration(); break;
	case 's': player.stopAcceleration(); break;
	case 'a': case 'd':
		player.stopTurning(); break;
	}
}

void City::myKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'w':
		player.accelerate();
		break;
	case 's':
		player.brake();
		break;
	case 'a':
		player.turnLeft();
		break;
	case 'd':
		player.turnRight();
		break;
	case '1':
		player.firstPerson();
		break;
	case '3':
		player.thirdPerson();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void City::myMotion(int x, int y) {
	player.handleMouseMotion(x, y);
}
void City::myMouse(int button, int state, int x, int y) {
	player.handleMouseButton(button, state, x, y);
}
void City::myReshape(int w, int h) {
	player.camera.setup(player.car.position, player.car.angle, player.car.front);
}

void City::update(float deltaTime) {

	player.update(deltaTime);

}