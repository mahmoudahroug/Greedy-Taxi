#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>  
#include "Car.h"
#include <vector>
#include <utility> // for std::pair


// Store gas tank positions
std::vector<std::pair<int, int>> gasTankPositions;
bool gasGenerated = false;
int WIDTH = 1280;
int HEIGHT = 720;

GLuint tex;
char title[] = "3D Model Loader Sample";


// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(20, 5, 20);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_road;
Model_3DS model_car;
Model_3DS model_rock;
Model_3DS model_fuel;
Model_3DS model_mountain;
Model_3DS model_chest;
Model_3DS model_cactus;
Model_3DS model_stone1;
Model_3DS model_stone2;
Model_3DS model_stone3;
Model_3DS model_bush;
// Textures
GLTexture tex_ground;
GLTexture tex_road;
Car car;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//
	car.init(Vector3(-5, 0.1, 7.5), Vector3(0.03, 0.03, 0.03),90, "models/car/xpander.3ds");
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
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

//=======================================================================
// Display Function
//=======================================================================

void drawGasTank(int x, int z) {
	glPushMatrix();
	glTranslatef(x, 0, z);
	glScalef(0.5, 0.5, 0.5);
	model_fuel.Draw();
	glPopMatrix();
}

void generateGas(int num) {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random generator

	for (int i = 0; i < num; i++) {
		int x = 15 + (i * 5); // Random x position
		int z = 4 + std::rand() % 8;            // Random z position
		gasTankPositions.emplace_back(x, z);    // Store position
	}
}

void drawGeneratedGasTanks() {
	for (const auto& pos : gasTankPositions) {
		drawGasTank(pos.first, pos.second); // Use stored positions
	}
}
void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Light setup
	GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	RenderGround();

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
	// Draw Car
	car.render();
	/*glPushMatrix();
	glTranslatef(-5, 0.1, 7.5);
	glScalef(0.03, 0.03, 0.03);
	glRotated(-90, 0, 1, 0);
	model_car.Draw();
	glPopMatrix();*/


	glColor3f(1, 1, 1);
	// Sandy Color for Rock
	glPushMatrix();
	glColor3f(194 / 255.0f, 178 / 255.0f, 128 / 255.0f); // Sandy color
	glRotated(90, 0, 1, 0);
	glTranslatef(5, 1.5, 10);
	glScalef(0.01, 0.01, 0.01);
	model_rock.Draw();
	glPopMatrix();
	if (!gasGenerated) {
		generateGas(25);  // Replace 5 with the number of tanks you want
		gasGenerated = true;
	}
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

	glutSwapBuffers();
}


//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		car.accelerate();
		break;
	case 's':
		car.reverse();
		break;
	case 'a':
		car.turnLeft();
		break;
	case 'd':
		car.turnRight();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{

	// Loading Model files
	model_house.Load("models/house/house.3DS");
	model_tree.Load("models/tree/Tree1.3ds");
	model_road.Load("models/road/untitled.3ds");
	model_car.Load("models/car/xpander.3ds");
	model_rock.Load("models/rock/arid_arch.3ds");
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
void update()
{
	static float lastTime = 0;
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000;
	lastTime = currentTime;

	car.update(deltaTime);
	glutPostRedisplay();
}
void keyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': car.stopAcceleration(); break;
	case 's': car.stopAcceleration(); break;
	case 'a': case 'd':
		car.stopTurning(); break;
	}
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutIdleFunc(update);
	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(keyboardUp);

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}