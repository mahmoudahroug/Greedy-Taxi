#pragma once
#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>  
#include <vector>
#include <utility> // for std::pair
#include "Player.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Vector3.h"
class Desert
{
public:
	// Store gas tank positions
	std::vector<GameObject> gasTanks;
	bool gasGenerated = false;
	Player player;
	CollisionManager collision;
	// Model Variables
	Model_3DS model_house;
	Model_3DS model_tree;
	Model_3DS model_road;
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
	GLuint tex;

	void init();
	void LoadAssets();
	void display();
	void update(float deltaTime);
	void myKeyboard(unsigned char key, int x, int y);
	void myMotion(int x, int y);
	void myMouse(int button, int state, int x, int y);
	void myReshape(int w, int h);
	void keyboardUp(unsigned char key, int x, int y);
private:
	void generateGas(int num);
	void renderGround();
	void drawGasTank(int x, int y);
	void drawGeneratedGasTanks();
	void checkCollision();
};

