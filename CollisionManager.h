#pragma once
#include "GameObject.h"



class CollisionManager
{
public:
	bool checkCollisionAABB(GameObject& o1, GameObject& o2);
	bool checkCollisionOBB(GameObject& o1, GameObject& o2);
};

