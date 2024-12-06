#include "City.h"

void City::display() {
	player.display();
	//glPushMatrix();
	//glScaled(0.4, 0.4, 0.4);
	model_city.Draw();
	//glPopMatrix();
	//model_taxi.Draw();
	for (int i = 0; i < model_city.numObjects; ++i) {
		if (model_city.Objects[i].boundingBox) {
			model_city.Objects[i].boundingBox->renderBoundingBox();
			model_city.Objects[i].boundingBox->renderNormals();
		}
	}
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
	model_city.CalculateBoundingBox();
	//model_taxi.Load("models/city_taxi/Taxi.3ds");
}

void City::checkCollisionObstacles() {
	// Iterate through objects in the Model_3DS
	for (int i = 0; i < model_city.numObjects; ++i) {
		// Check if the bounding box exists
		if (!model_city.Objects[i].boundingBox) {
			continue;
		}

		GameObject& cityObject = *model_city.Objects[i].boundingBox;
		//cityObject.renderBoundingBox();
		// Perform collision checks

		//bool aabbCollision = collision.checkCollisionAABB(player.car, cityObject);
		//bool obbCollision = collision.checkCollisionOBB(player.car, cityObject);
		std::string objectName(model_city.Objects[i].name);
		if (collision.checkCollisionAABB(player.car, cityObject) && i!=366 && objectName.find("LM_Basketball") == std::string::npos) {

			CollisionResult obbCollision = collision.checkCollision(player.car, cityObject);
			if (!obbCollision.isColliding) {
				continue;
			}
			// Print details of the game object only when a collision occurs
			std::cout << "Collision detected with object: " << model_city.Objects[i].name << '\n';
			std::cout << "Object Bounding Box:\n";
			std::cout << " Position: (" << cityObject.position.x << ", "
				<< cityObject.position.y << ", " << cityObject.position.z << ")\n";
			std::cout << " Size: (" << cityObject.size.x << ", "
				<< cityObject.size.y << ", " << cityObject.size.z << ")\n";

			// Log player car information
			std::cout << "Player Car Bounding Box:\n";
			std::cout << " Position: (" << player.car.position.x << ", "
				<< player.car.position.y << ", " << player.car.position.z << ")\n";
			std::cout << " Size: (" << player.car.size.x << ", "
				<< player.car.size.y << ", " << player.car.size.z << ")\n";
			std::cout << " Collision Normal: (" << obbCollision.collisionNormal.x << ", "
				<< obbCollision.collisionNormal.y << ", " << obbCollision.collisionNormal.z << ")\n";

			//if(obbCollision.collisionNormal == Vector3(0, 0, 1))
			//	obbCollision.collisionNormal = Vector3(0, 0, -1);
			player.setCollisionNormal(obbCollision.collisionNormal);
			// Handle collision
			playCollisionSound();
			
			return; // Exit after handling the collision
		}
	}
}




void City::playCollisionSound() {
	if (engine1) engine1->play2D("sounds/collision.mp3", false);
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
	checkCollisionObstacles();
	player.update(deltaTime);

}