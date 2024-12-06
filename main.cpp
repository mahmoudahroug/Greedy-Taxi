#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>  
#include <vector>
#include <glut.h>
#include "irrKlang.h"
#include "Desert.h"
#include "City.h"
#include "Sun.h"
using namespace irrklang;

ISoundEngine* engine = nullptr;
void playHornSound();
int WIDTH = 1280;
int HEIGHT = 720;

int level = 1;

GLuint tex;
char title[] = "Greedy Taxi";

Sun sun(0.0f, 10.0f);
GLTexture tex_ground;
Desert desert;
City city;

Model_3DS model_city;

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
void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	InitLightSource();

	InitMaterial();
	city.init();
	desert.init();


	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Display Function
//=======================================================================

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//// Draw Ground
	//RenderGround();
	sun.applyLight();


	if (level == 1)
		city.display();
	else
		desert.display();
	//glPushMatrix();
	//glScaled(0.1, 0.1, 0.1);
	//model_city.Draw();
	//glPopMatrix();

	glutSwapBuffers();
}


//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char key, int x, int y)
{
	if (level == 1)
		city.myKeyboard(key, x, y);
	else
		desert.myKeyboard(key, x, y);

	switch (key) {
	case 'h':
		playHornSound();
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
	if (level == 1)
		city.myMotion(x, y);
	else
		desert.myMotion(x, y);

	//GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	if (level == 1)
		city.myMouse(button, state, x, y);
	else
		desert.myMouse(button, state, x, y);
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
	if (level == 1)
		city.myReshape(w, h);
	else
		desert.myReshape(w, h);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{

	//// Loading Model files

	city.LoadAssets();
	desert.LoadAssets();
	//model_city.Load("models//city/city.3ds");
	//tex_ground.Load("Textures/sand1.bmp");
	//tex_road.Load("models/road/untitled.bmp");
	//loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}
void switchLevel(int value) {
	level = 2;

}
void update()
{
	static float lastTime = 0;
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000;
	lastTime = currentTime;

	sun.update(deltaTime);           // Update the sun's position and properties
	if (level == 1)
		city.update(deltaTime);
	else
		desert.update(deltaTime);

	
	if (city.checkGameWin() && level == 1) {
		//level = 2;
		//	//unload level 1 assets
		glutTimerFunc(500, switchLevel, 1);
	}

	glutPostRedisplay();
}
void keyboardUp(unsigned char key, int x, int y) {
	if (level == 1)
		city.keyboardUp(key, x, y);
	else
		desert.keyboardUp(key, x, y);
}

//void playAnimationSound() {
//	if (engine) engine->play2D(ANIMATION_SOUND_PATH, false);
//}
//
//void playCollisionSound() {
//	if (engine) engine->play2D(COLLISION_SOUND_PATH, false);
//}
void playHornSound() {
	if (engine) engine->play2D("sounds/horn1.mp3", false);
}
//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(0, 0);

	glutCreateWindow(title);

	//Camera::instance = &mainCamera;
	engine = createIrrKlangDevice();
	if (!engine) {
		std::cerr << "Sound engine could not start." << std::endl;
	}
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