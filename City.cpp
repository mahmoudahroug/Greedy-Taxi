#include "City.h"

void City::generateCash(int num) {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random generator

	for (int i = 0; i < num; i++) {

		//bounds for cash
		const float xMin = -370.165f;
		const float xMax = 170.037f;
		const float zMin = -224.158f;
		const float zMax = 0.0f;

		float x = xMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (xMax - xMin)));
		float z = zMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (zMax - zMin)));

		GameObject g;
		g.init(Vector3(x, 0, z), Vector3(1, 1, 1.2), Vector3(5, 5, 5), 0, "models/cash/cash.3DS");
		while (!canPlace(g))
		{
			x = xMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (xMax - xMin)));
			z = zMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (zMax - zMin)));
			g.init(Vector3(x, 0, z), Vector3(1, 1, 1.2), Vector3(5, 5, 5), 0, "models/cash/cash.3DS");
		}
		cashBlocks.emplace_back(g);    // Store position
	}
}

void City::drawGeneratedCashBlocks() {
	for (auto& cash : cashBlocks) {
		cash.render();
	}
}

void City::display() {
	if (gameWon || gameLost) {
		displayGameEndScreen();
	}
	else {
		player.display();

		glPushMatrix();
		//glScaled(0.4, 0.4, 0.4);
		model_city.Draw();
		drawGeneratedCashBlocks();
		glPopMatrix();
		//model_taxi.Draw();
		for (int i = 0; i < model_city.numObjects; ++i) {
			if (model_city.Objects[i].boundingBox) {
				model_city.Objects[i].boundingBox->renderBoundingBox();
				//model_city.Objects[i].boundingBox->renderNormals();
			}
		}


		// Display Game Score
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 1280, 720, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor3f(0.0f, 1.0f, 0.0f);
		std::string scoreText = "Score: " + std::to_string(collectedCash) + "/10";
		glRasterPos2i(10, 20);
		for (char c : scoreText) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}

		glColor3f(1.0f, 0.0f, 0.0f);
		int timerInt = static_cast<int>(std::ceil(gameTimer));
		std::string timerText = "Time: " + std::to_string(timerInt);
		glRasterPos2i(10, 50);
		for (char c : timerText) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
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


	generateCash(100);

	//model_taxi.Load("models/city_taxi/Taxi.3ds");
}


bool City::canPlace(GameObject g) {
	//numOnjects 0,when loaded first, gives nptr
	//std::cout << "Testing placement at (" << x << ", " << z << "numObjects: " << model_city.numObjects << ")\n";
	std::cout << "noOfModels: " << model_city.numObjects << std::endl;
	for (int i = 0; i < model_city.numObjects; ++i) {

		// Check if the bounding box exists
		if (!model_city.Objects[i].boundingBox) {
			continue;
		}

		GameObject& cityObject = *model_city.Objects[i].boundingBox;	
		std::string objectName(model_city.Objects[i].name);
		// Check collision
		if (collision.checkCollisionAABB(g, cityObject) && i != 366 && objectName.find("LM_Basketball") == std::string::npos) {

			CollisionResult obbCollision = collision.checkCollision(g, cityObject);
			if (obbCollision.isColliding) {
				return false;
			}
		}
	}
	std::cout << "Placement successful.\n";
	return true;
}


void City::displayGameEndScreen() {
	int width = 1280;
	int height = 720;
	// Set the background to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear color and depth buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set background color to black

	// Switch to orthographic projection for 2D rendering (text rendering)
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);  // Set up 2D orthographic projection

	glMatrixMode(GL_MODELVIEW);  // Switch back to the modelview matrix

	// Reset the modelview matrix to avoid transformation issues
	glPushMatrix();
	glLoadIdentity();

	// Set the text color to white
	glColor3f(1.0f, 0.0f, 0.0f);

	// Display "GAME WIN!" if the player wins
	if (gameWon) {

		glColor3f(0, 1, 0);
		std::string winText = "Congratulations! You Advance to the Next Level";
		glRasterPos2i(width / 2 - 150, height / 2);  // Adjust position for the text (top-center)
		//playWonSound();
		// Render each character of the text
		for (char c : winText) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);  // Render each character
		}
	}
	// Display "GAME LOSE!" if the player loses
	else if (gameLost) {
		glColor3f(1.0f, 0.0f, 0.0f);
		std::string loseText = "GAME LOSE! You Fail to Advance to Next Level :(";
		glRasterPos2i(width / 2 -150, height / 2); // Adjust position for the text (top-center)
		// Render each character of the text
		for (char c : loseText) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);  // Render each character
		}
	}

	// Pop the modelview matrix and projection matrix to restore the previous settings
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Ensure everything is rendered to the screen
	glFlush();
}

void City::checkCollisionCollectables() {
	for (auto it = cashBlocks.begin(); it != cashBlocks.end(); ) {
		if (collision.checkCollisionAABB(player.car, *it) && collision.checkCollisionOBB(player.car, *it)) {
			playCollectibleSound();
			it = cashBlocks.erase(it); // Remove collided gas tank and update iterator
			collectedCash++;
		}
		else {
			++it; // Only increment if no collision to avoid skipping elements
		}
	}
}

void City::checkCollisionBoundaries() {
	//bounds for map
	const float xMin = -385.165f;
	const float xMax = 170.037f;
	const float zMin = -224.158f;
	const float zMax = 8.0f;

	// Check if player is beyond the lower boundary
	if (player.getPosition().z < zMin) {
		player.setCollisionNormal(Vector3(0, 0, 1));
		playBoundariesSound();
	}
	// Check if player is beyond the upper boundary
	if (player.getPosition().z > zMax) {
		player.setCollisionNormal(Vector3(0, 0, -1));
		playBoundariesSound();

	}

	// Check if player is beyond the lower boundary
	if (player.getPosition().x < xMin) {
		player.setCollisionNormal(Vector3(1, 0, 0));
		playBoundariesSound();

	}
	// Check if player is beyond the upper boundary
	if (player.getPosition().x > xMax) {
		player.setCollisionNormal(Vector3(-1, 0, 0));
		playBoundariesSound();

	}
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

			player.setCollisionNormal(obbCollision.collisionNormal);
			// Handle collision
			playCollisionSound();
			
			//return; // Exit after handling the collision
		}
	}
}




void City::playCollisionSound() {
	if (engine1) engine1->play2D("sounds/collision.mp3", false);
}

void City::playCollectibleSound() {
	if (engine1) engine1->play2D("sounds/collectible.mp3", false);
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
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		player.toggleViewMode();
	}
}
void City::myReshape(int w, int h) {
	player.camera.setup(player.car.position, player.car.angle, player.car.front);
}

void City::playWonSound() {
	if (engine1) engine1->play2D("sounds/congrats.mp3", false);
}

void City::playLostSound() {
	if (engine1) engine1->play2D("sounds/lost.mp3", false);
}
void City::playBoundariesSound() {
	if (engine1) engine1->play2D("sounds/win2.wav", false);
}
bool City::checkGameWin() {
	return gameWon;
}
void City::update(float deltaTime) {
	if (gameWon || gameLost) {
		return;
	}
	lastSecondTime += deltaTime;

	// Decrement timer every second
	if (lastSecondTime >= 1.0f) {
		gameTimer--;  // Reduce by 1 second
		lastSecondTime = 0.0f;  // Reset second tracker
	}

	// Ensure timer doesn't go below zero
	if (gameTimer < 0) {
		gameTimer = 0;
	}

	checkCollisionObstacles();
	checkCollisionCollectables();
	checkCollisionBoundaries();
	if (collectedCash == 10) {
		gameWon = true;
		collectedCash++;
		playWonSound();
	}
	if (gameTimer == 0 && collectedCash < 10) {
		gameLost = true;
		playLostSound();
		gameTimer--;
	}
	player.update(deltaTime);

	//std::cout << "pos: " << player.getPosition().x << ", " << player.getPosition().y << ", " << player.getPosition().z << "\n";
}