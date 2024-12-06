#include "Desert.h"
#include "TextureBuilder.h"
void Desert::generateGas(int num) {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random generator

	for (int i = 0; i < num; i++) {
		float x = 50 + (i * 50); // Random x position
		float zPos[] = { 5.5, 9.3, 5.8, 7.7 };

		// Select a random index for the first cactus
		int z = rand() % 4;
		while (!isGasTankAtPosition(x,zPos[z]))
		{
			z = rand() % 4;
		}
		GameObject g;
		g.init(Vector3(x, 0, zPos[z]),   Vector3(1, 1, 1.2),  Vector3(0.5, 0.5, 0.5), 0, "models/fuel/gas.3DS");
		gasTanks.emplace_back(g);    // Store position
	}
}
void Desert::generateObstacles(int num) {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random generator

	for (int i = 0; i < num; i++) {
		float x = 25 + (i * 25); // Random x position
		float zPos[] = { 3.5, 9.3, 5.8, 7.5 };

		// Select a random index for the first cactus
		int index1 = rand() % 4;
		GameObject g;
		g.init(Vector3(x, 0.2, zPos[index1]), Vector3(1, 0.3, 1.5), Vector3(0.1, 0.1, 0.1), 90, "models/cactus/cactus1.3ds");
		obstacles.emplace_back(g);    
	}
}
void Desert::init() {
	generateObstacles(50);
	fuel = 100.0f;
	player.init(Vector3(-5, 0.1, 7.5), Vector3(1, 1, 2.3), Vector3(-0.02, 0.02, -0.02), 90, "models/car/xpander.3ds");
	generateGas(25);
	
	treasure.initcolor(Vector3(1300, 0, 7.5), Vector3(0.5, 0.5, 0.5),Vector3(101 / 255.0f, 67 / 255.0f, 33 / 255.0f), -90, "models/chest/chest.3ds");

	

	Camera::instance1 = &player.camera;
	engine1 = createIrrKlangDevice();
	if (!engine1) {
		std::cerr << "Sound engine could not start." << std::endl;
	}
}
void Desert::renderGround()
{
	//glDisable(GL_LIGHTING);	// Disable lighting 

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-1500, 0, -1500);
	glTexCoord2f(5, 0);
	glVertex3f(1500, 0, -1500);
	glTexCoord2f(5, 5);
	glVertex3f(1500, 0, 1500);
	glTexCoord2f(0, 5);
	glVertex3f(-1500, 0, 1500);
	glEnd();
	glPopMatrix();

	//glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}


void Desert::drawGeneratedGasTanks() {
	for (auto& tank : gasTanks) {
		tank.render();
	}
}
void Desert::drawGeneratedObstacles() {
	for (auto& o : obstacles) {
		
		glPushMatrix();
		glTranslatef(o.position.x, o.position.y + o.size.y / 2, o.position.z);
		glScalef(o.size.x, o.size.y, o.size.z);
		glutWireCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(o.position.x, o.position.y, o.position.z-0.7);
		glRotatef(o.angle, 1, 0, 0);
		glScalef(o.extraScaling.x, o.extraScaling.y, o.extraScaling.z);
		glColor3f(0.4f, 0.5f, 0.1f);
		o.model.Draw();
		glPopMatrix();

		
	}
}
void Desert::checkCollision() {
	for (auto it = gasTanks.begin(); it != gasTanks.end(); ) {
		if (collision.checkCollisionAABB(player.car, *it) && collision.checkCollisionOBB(player.car, *it)) {
			if (!(gameWon||gameLost))
				playCollectibleSound();
			if(!gameLost)
				refuel(20.0f);
			it = gasTanks.erase(it); // Remove collided gas tank and update iterator
		}
		else {
			++it; // Only increment if no collision to avoid skipping elements
		}
	}
}
void Desert::checkCollisionTreasure() {
	
	if (collision.checkCollisionAABB(player.car, treasure) && collision.checkCollisionOBB(player.car, treasure)) {
		playTreasureSound();
		isCollected = true;
		gameWon = true;
	}
	}
		
			
	

void Desert::checkCollisionObstacles() {
	for (auto it = obstacles.begin(); it != obstacles.end(); ) {
		if (collision.checkCollisionAABB(player.car, *it) && collision.checkCollisionOBB(player.car, *it)) {
			if (!(gameWon || gameLost))
				playCollisionSound();
			fuel = fuel - 10;
			it=obstacles.erase(it);
		}
		else {
			++it; // Only increment if no collision to avoid skipping elements
		}
	}
}

void Desert::checkCollisionBoundaries(float deltaTime) {
	float lowerBoundary = 4.0f;
	float upperBoundary = 11.0f;

	// Check if player is beyond the lower boundary
	if (player.getPosition().z < lowerBoundary) {
		player.setCollisionNormal(Vector3(0, 0, 1));
		playBoundariesSound();
	}
	// Check if player is beyond the upper boundary
	else if (player.getPosition().z > upperBoundary) {
		player.setCollisionNormal(Vector3(0, 0, -1));
		playBoundariesSound();
	}

	//// Apply smooth recoil to position using velocity
	//if (player.car.velocity.z != 0) {
	//	player.car.position.z += player.car.velocity.z * deltaTime;

	//	// Stop recoil when back within boundaries
	//	if ((player.car.velocity.z > 0 && player.car.position.z >= lowerBoundary + 5.0f) ||
	//		(player.car.velocity.z < 0 && player.car.position.z <= upperBoundary - 5.0f)) {
	//		player.car.velocity.z = 0;  // Stop recoil
	//		//std::cout << "Car stopped recoil at z: " << player.car.position.z << "\n";
	//	}
	//}
}

void Desert::displayGameEndScreen() {
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
	if (isCollected&& player.getPosition().x>1350) {

		std::string winText = "GAME WIN!";
		glRasterPos2i(width / 2, height / 2);  // Adjust position for the text (top-center)
		//playWonSound();
		// Render each character of the text
		for (char c : winText) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);  // Render each character
		}
	}
	// Display "GAME LOSE!" if the player loses
	else if ((!isCollected && player.getPosition().x > 1350)||fuel<=0) {

		std::string loseText = "GAME LOSE!";
		glRasterPos2i(width / 2, height / 2); // Adjust position for the text (top-center)
		//playLostSound();
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
void Desert::drawFuelBar() {
	float fuelPercentage = fuel / 100.0f;  // Calculate fuel as a percentage

	// Set the position and size of the fuel bar
	float barWidth = 300.0f * fuelPercentage;  // Bar length based on fuel
	float barHeight = 20.0f;
	float screenPadding = 10.0f;  // Distance from the screen edge

	// Switch to 2D orthographic projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluOrtho2D(0, viewport[2], 0, viewport[3]);  // Set orthographic projection to screen size

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Calculate position for the top-right corner
	float barX = viewport[2] - barWidth - screenPadding;  // Right side with padding
	float barY = viewport[3] - barHeight - screenPadding;  // Top side with padding

	// Draw the background (empty bar)
	glColor3f(0.5f, 0.5f, 0.5f);  // Gray color
	glRectf(barX, barY, barX + 300.0f, barY + barHeight);

	// Draw the fuel level (filled part)
	glColor3f(0.0f, 1.0f, 0.0f);  // Green color for fuel
	glRectf(barX, barY, barX + barWidth, barY + barHeight);

	// Restore the previous matrix state
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);  // Reset to the model view matrix
}

bool Desert::isGasTankAtPosition(float x, float z) {
	// Define a threshold for proximity comparison
	const float threshold =	2;  // You can adjust this based on the size of obstacles

	// Iterate through all obstacles and compare x and z coordinates
	for ( auto& obstacle : obstacles) {
		// Get the position of the obstacle (assuming the position is stored in Vector3)
		float obstacleX = obstacle.position.x;
		float obstacleZ = obstacle.position.z;

		// Check if the x and z coordinates are close to the desired position
		if (std::abs(obstacleX - x) < threshold && std::abs(obstacleZ - z) < threshold) {
			return false;  // A gas tank already exists at this position
		}
	}

	return true;  // No gas tank at the given position
}
void Desert::display() {


	if (player.getPosition().x>1350 || fuel<=0) {
	
		
		displayGameEndScreen();
	}
	else {
		player.display();
		// Draw Ground
		renderGround();

	
		// Infinite Road
		for (float z = -10; z < 1500; z += 2.0f) // Adjust spacing if needed
		{
			glPushMatrix();
			glTranslatef(z, -1, 10);
			glScalef(1, 1, 1);
			model_road.Draw();
			glPopMatrix();
		}
		for (float z = -10; z < 1500; z += 2.0f) // Adjust spacing if needed
		{
			glPushMatrix();
			glTranslatef(z, -1, 5.6);
			glScalef(1, 1, 1);
			model_road.Draw();
			glPopMatrix();
		}

		drawGeneratedGasTanks();
		drawFuelBar();
		drawGeneratedObstacles();


		for (float z = 0; z < 1350; z += 75.0f) {
			// Draw Bushes
			glPushMatrix();
			glTranslatef(5 + z, 0, 18);
			glScalef(0.05, 0.05, 0.05);
			glColor3f(0.3f, 0.3f, 0.1f);
			model_bush.Draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(6 + z, 0, 19);
			glScalef(0.05, 0.05, 0.05);
			glColor3f(0.3f, 0.3f, 0.1f);
			model_bush.Draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(12.5 + z, 0, 18);
			glScalef(0.05, 0.05, 0.05);
			glColor3f(0.3f, 0.3f, 0.1f);
			model_bush.Draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(13.5 + z, 0, 19);
			glScalef(0.05, 0.05, 0.05);
			glColor3f(0.3f, 0.3f, 0.1f);
			model_bush.Draw();
			glPopMatrix();

			// Draw Stones
			glPushMatrix();
			glTranslatef(7 + z, -1, 14);
			glScalef(0.07, 0.07, 0.07);
			glRotatef(90.f, 0, 1, 0);
			glColor3f(194 / 255.0f, 178 / 255.0f, 128 / 255.0f);
			model_stone1.Draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(8 + z, -1, 16.5);
			glScalef(0.06, 0.06, 0.06);
			glRotatef(90.f, 0, 1, 0);
			glColor3f(194 / 255.0f, 178 / 255.0f, 128 / 255.0f);
			model_stone1.Draw();
			glPopMatrix();
		}



		glPushMatrix();
		glTranslatef(20, 7, -50);
		glScalef(0.4, 0.4, 0.4);
		model_mountain.Draw();
		glPopMatrix();




		glColor3f(1, 1, 1);
		// Sandy Color for Rock
		glPushMatrix();
		glColor3f(194 / 255.0f, 178 / 255.0f, 128 / 255.0f); // Sandy color
		glRotated(90, 0, 1, 0);
		glTranslatef(5, 1.5, 10);
		glScalef(0.01, 0.01, 0.01);
		model_rock.Draw();
		glPopMatrix();

		// Draw Cactus
		glPushMatrix();
		for (float z = 0; z < 1350; z += 5.0f) {
			glPushMatrix();
			glTranslatef(-5 + (z * 3), 0, 2);
			glScalef(0.1, 0.1, 0.1);
			glRotatef(90.f, 0, 1, 0);
			glColor3f(0.4f, 0.5f, 0.1f);
			model_cactus.Draw();
			glPopMatrix();
		}
		glPopMatrix();
		treasure.renderColor();
		// Reset color to white for subsequent objects
		glColor3f(1, 1, 1);

		// Draw House
		glPushMatrix();
		glTranslatef(25, 0, -15);
		glRotatef(90.f, 1, 0, 0);
		glRotatef(45.f, 0, 0, 1);

		model_house.Draw();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(40, 0, -18);
		model_tree.Draw();
		glPopMatrix();
		//// Skybox (Sphere)
		glPushMatrix();
		GLUquadricObj* qobj = gluNewQuadric();
		glTranslated(800, 0, 0);
		glRotated(90, 1, 0, 1);
		glBindTexture(GL_TEXTURE_2D, tex);
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 900, 900, 900);
		gluDeleteQuadric(qobj);
		glPopMatrix();
	}
}

void Desert::LoadAssets()
{

	// Loading Model files
	model_house.Load("models/house/house.3DS");
	model_tree.Load("models/tree/Tree1.3ds");
	model_road.Load("models/road/untitled.3ds");
	//model_rock.Load("models/rock/arid_arch.3ds");
	model_fuel.Load("models/fuel/gas.3DS");
	model_mountain.Load("models/mountain/mountain.3DS");
	model_chest.Load("models/chest/chest.3ds");
	model_cactus.Load("models/cactus/cactus1.3ds");
	model_stone1.Load("models/stones/stone1.3ds");
	model_stone2.Load("models/stones/stone2.3ds");
	model_bush.Load("models/bush/bush2.3ds");
	// Loading texture files
	tex_ground.Load("Textures/sand1.bmp");
	//tex_road.Load("models/road/untitled.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}
void Desert::update(float deltaTime) {
	checkCollision();
	checkCollisionBoundaries(deltaTime);
	checkCollisionObstacles();  // Check for collisions in every frame
	checkCollisionTreasure();
	player.update(deltaTime);
	
	fuel -= player.getSpeed() * 0.01f;
	
	if (fuel < 0) {
		fuel = 0;
		player.brake();
		gameLost = true;
		
	} // Ensure fuel doesn't go negative
	if (player.getPosition().x > 1350 || fuel<=0) {
		if (gameLost && !sound) {
			playLostSound();
			sound = true;
		}
		else if (gameWon && !sound) {
			playWonSound();
			sound = true;
		}
	}
}
void Desert::myKeyboard(unsigned char key, int x, int y) {
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
void Desert::myMotion(int x, int y) {
	player.handleMouseMotion(x, y);
}
void Desert::myMouse(int button, int state, int x, int y) {
	player.handleMouseButton(button, state, x, y);
}
void Desert::myReshape(int w, int h) {
	player.camera.setup(player.car.position, player.car.angle, player.car.front);
}
void Desert::keyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': player.stopAcceleration(); break;
	case 's': player.stopAcceleration(); break;
	case 'a': case 'd':
		player.stopTurning(); break;
	}
}
void Desert::playCollectibleSound() {
	if (engine1) engine1->play2D("sounds/collectible.mp3", false);
}void Desert::playCollisionSound() {
	if (engine1) engine1->play2D("sounds/collision.mp3", false);
}void Desert::playTreasureSound() {
	if (engine1) engine1->play2D("sounds/treasure.mp3", false);
}void Desert::playWonSound() {
	if (engine1) engine1->play2D("sounds/won.mp3", false);
}void Desert::playLostSound() {
	if (engine1) engine1->play2D("sounds/lost.mp3", false);
}
void Desert::playBoundariesSound() {
	if (engine1) engine1->play2D("sounds/win2.wav", false);
}