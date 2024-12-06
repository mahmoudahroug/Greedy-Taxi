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
#include "irrKlang.h"
using namespace irrklang;


class City
{
public:
	std::vector<GameObject> obstacles;
	ISoundEngine* engine1 = nullptr;
	GameObject cash;
	bool isCollected = false;
	bool gameWon = false;
	bool gameLost = false;
	std::vector<GameObject> cashBlocks;
	Player player;
	CollisionManager collision;
	// Model Variables
	// Textures
	Model_3DS model_city;
	Model_3DS model_taxi;
	void init();
	void LoadAssets();
	void generateCash(int num);
	void drawGeneratedCashBlocks();
	void display();
	void update(float deltaTime);
	bool canPlace(float x, float z);
	void playCollectibleSound();
	void checkCollisionCollectables();
	void checkCollisionObstacles();
	void playCollisionSound();
	void myKeyboard(unsigned char key, int x, int y);
	void myMotion(int x, int y);
	void myMouse(int button, int state, int x, int y);
	void myReshape(int w, int h);
	void keyboardUp(unsigned char key, int x, int y);

};