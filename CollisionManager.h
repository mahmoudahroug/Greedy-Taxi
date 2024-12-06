#pragma once
#include "GameObject.h"
#include "Model_3DS.h"
#include "Player.h"

struct CollisionResult {
    bool isColliding;
    Vector3 collisionNormal;
};

class CollisionManager
{
public:
	bool checkCollisionAABB(GameObject& o1, GameObject& o2);
	bool checkCollisionOBB(GameObject& o1, GameObject& o2);
	CollisionResult checkCollision(GameObject& o1, GameObject& o2);
	CollisionResult checkCollision(Player& player, Model_3DS& model);
};

