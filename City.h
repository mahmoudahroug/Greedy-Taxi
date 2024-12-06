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
private:
	float gameTimer = 60.0f;  // Start at 60 seconds
	float lastSecondTime = 0.0f;  // Track last time a second passed
public:
	ISoundEngine* engine1 = nullptr;
	int collectedCash = 0;
	GameObject cash;
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
	bool canPlace(GameObject g);
	void displayGameEndScreen();
	void playWonSound();
	void playLostSound();
	void playCollectibleSound();
	void playBoundariesSound();
	void checkCollisionCollectables();
	void checkCollisionObstacles();
	void checkCollisionBoundaries();
	bool checkGameWin();
	void playCollisionSound();
	void myKeyboard(unsigned char key, int x, int y);
	void myMotion(int x, int y);
	void myMouse(int button, int state, int x, int y);
	void myReshape(int w, int h);
	void keyboardUp(unsigned char key, int x, int y);

};