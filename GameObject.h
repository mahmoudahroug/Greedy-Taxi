#pragma once
#include "Vector3.h"
#include "Model_3DS.h"
#include <vector>
#include <iostream>
class GameObject
{
public:
	Vector3 position; // Center of object
	Vector3 size;     // Dimensions of the object (width, height, depth)
	Vector3 extraScaling;
	Vector3 front; // Front vector of object
	Vector3 right; // Right vector of object
	Vector3 up;
	Model_3DS model; // 3D model of object
	float angle;
	float pitch;
	float maxSide;
	void init(Vector3 pos, Vector3 s, int a, char* m);
	void init(Vector3 pos, Vector3 s, Vector3 extraS, int a, char* m);
	
	void render();
	GameObject() {
		position = Vector3(0, 0, 0);
		size = Vector3(1, 1, 1);
		extraScaling = Vector3(1, 1, 1);
		model = Model_3DS();
		front = Vector3(0, 0, 1);
		right = Vector3(1, 0, 0);
		up = Vector3(0, 1, 0);
		angle = 0;
		pitch = 0;
		maxSide = size.x > size.z ? size.x : size.z;
	}
	//GameObject(Vector3 pos, Vector3 s, Model_3DS* m) {
	//	position = pos;
	//	size = s;
	//	model = m;
	//	front = Vector3(0, 0, 1);
	//	right = Vector3(1, 0, 0);
	//	angle = 0;
	//	pitch = 0;
	//	maxSide = size.x > size.z ? size.x : size.z;
	//}
	Vector3 getMin() {
		return position - Vector3(maxSide, size.y, maxSide) * 0.5;
	}
	Vector3 getMax() {
		return position + Vector3(maxSide, size.y, maxSide) * 0.5;
	}
	std::vector<Vector3> getVertices();

	void renderBoundingBox();
protected:
	void rotate(float rad);
};

