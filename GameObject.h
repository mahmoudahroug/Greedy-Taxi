#pragma once
#include "Vector3.h"
#include "Model_3DS.h"
class GameObject
{
public:
	Vector3 position; // Center of object
	Vector3 size;     // Dimensions of the object (width, height, depth)
	Vector3 front; // Front vector of object
	Vector3 right; // Right vector of object
	Model_3DS model; // 3D model of object
	float angle;
	void renderBoundingBox();
};

