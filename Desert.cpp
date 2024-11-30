#include "Desert.h"
#include "TextureBuilder.h"
void Desert::generateGas(int num) {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random generator

	for (int i = 0; i < num; i++) {
		int x = 15 + (i * 5); // Random x position
		int z = 4 + std::rand() % 8;            // Random z position
		gasTankPositions.emplace_back(x, z);    // Store position
	}
}
void Desert::init() {
	player.init(Vector3(-5, 0.1, 7.5), Vector3(1, 1, 1), 90, "models/car/xpander.3ds");
	generateGas(25);
	Camera::instance = &player.camera;
}
void Desert::renderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-200, 0, -200);
	glTexCoord2f(5, 0);
	glVertex3f(200, 0, -200);
	glTexCoord2f(5, 5);
	glVertex3f(200, 0, 200);
	glTexCoord2f(0, 5);
	glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
void Desert::drawGasTank(int x, int z) {
	glPushMatrix();
	glTranslatef(x, 0, z);
	glScalef(0.5, 0.5, 0.5);
	model_fuel.Draw();
	glPopMatrix();
}

void Desert::drawGeneratedGasTanks() {
	for (const auto& pos : gasTankPositions) {
		drawGasTank(pos.first, pos.second); // Use stored positions
	}
}
void Desert::display() {

	// Light setup
	GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	player.display();
	// Draw Ground
	renderGround();

	// Infinite Road
	for (float z = -200; z < 200; z += 2.0f) // Adjust spacing if needed
	{
		glPushMatrix();
		glTranslatef(z, -1, 10);
		glScalef(1, 1, 1);
		model_road.Draw();
		glPopMatrix();
	}
	for (float z = -200; z < 200; z += 2.0f) // Adjust spacing if needed
	{
		glPushMatrix();
		glTranslatef(z, -1, 5.6);
		glScalef(1, 1, 1);
		model_road.Draw();
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(20, 7, -50);
	glScalef(0.4, 0.4, 0.4);
	model_mountain.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(20, 1, 20);
	glRotated(180, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	model_chest.Draw();
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

	drawGeneratedGasTanks();

	// Draw Cactus
	glPushMatrix();
	for (int i = 0; i < 7; ++i) {
		glPushMatrix();
		glTranslatef(-5 + (i * 3), 0, 3);
		glScalef(0.1, 0.1, 0.1);
		glRotatef(90.f, 0, 1, 0);
		glColor3f(0.4f, 0.5f, 0.1f);
		model_cactus.Draw();
		glPopMatrix();
	}
	glPopMatrix();

	// Draw Stones 
	glPushMatrix();
	glTranslatef(-5, -1, 14);
	glScalef(0.09, 0.09, 0.09);
	glRotatef(90.f, 0, 1, 0);
	glColor3f(194 / 255.0f, 178 / 255.0f, 128 / 255.0f);
	model_stone1.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5, -1, 16.5);
	glScalef(0.09, 0.09, 0.09);
	glRotatef(90.f, 0, 1, 0);
	glColor3f(194 / 255.0f, 178 / 255.0f, 128 / 255.0f);
	model_stone1.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, -1, 14);
	glColor3f(194 / 255.0f, 178 / 255.0f, 128 / 255.0f);
	model_stone2.Draw();
	glPopMatrix();

	// Draw Rock
	glPushMatrix();
	glColor3f(194 / 255.0f, 178 / 255.0f, 128 / 255.0f); // Sandy color
	glRotated(90, 0, 1, 0);
	glTranslatef(5, 1.5, 10);
	glScalef(0.01, 0.01, 0.01);
	model_rock.Draw();
	glPopMatrix();

	// Draw Bush
	glPushMatrix();
	glTranslatef(5, 0, 14);
	glScalef(0.05, 0.05, 0.05);
	glColor3f(0.3f, 0.3f, 0.1f);
	model_bush.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 0, 15);
	glScalef(0.05, 0.05, 0.05);
	glColor3f(0.3f, 0.3f, 0.1f);
	model_bush.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12.5, 0, 14);
	glScalef(0.05, 0.05, 0.05);
	glColor3f(0.3f, 0.3f, 0.1f);
	model_bush.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13.5, 0, 14);
	glScalef(0.05, 0.05, 0.05);
	glColor3f(0.3f, 0.3f, 0.1f);
	model_bush.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7, 0, 18);
	glScalef(0.05, 0.05, 0.05);
	glColor3f(0.3f, 0.3f, 0.1f);
	model_bush.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 0, 19);
	glScalef(0.05, 0.05, 0.05);
	glColor3f(0.3f, 0.3f, 0.1f);
	model_bush.Draw();
	glPopMatrix();

	// Reset color to white for subsequent objects
	glColor3f(1, 1, 1);

	//// Draw House
	//glPushMatrix();
	//glRotatef(90.f, 1, 0, 0);
	//model_house.Draw();
	//glPopMatrix();

	//// Skybox (Sphere)
	glPushMatrix();
	GLUquadricObj* qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);
	glPopMatrix();
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
	player.update(deltaTime);
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
	glutPostRedisplay();
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