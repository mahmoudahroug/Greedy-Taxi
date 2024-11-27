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
	float pitch;
	GameObject() {
		position = Vector3(0, 0, 0);
		size = Vector3(1, 1, 1);
		front = Vector3(0, 0, 1);
		right = Vector3(1, 0, 0);
		angle = 0;
	}
	void renderBoundingBox();
};

