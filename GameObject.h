#pragma once
#include "Vector3.h"
#include "Model_3DS.h"
#include <vector>
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
	float maxSide;
	GameObject() {
		position = Vector3(0, 0, 0);
		size = Vector3(1, 1, 1);
		model = Model_3DS();
		front = Vector3(0, 0, 1);
		right = Vector3(1, 0, 0);
		angle = 0;
		pitch = 0;
		maxSide = size.x > size.z ? size.x : size.z;
	}
	GameObject(Vector3 pos, Vector3 s, Model_3DS m) {
		position = pos;
		size = s;
		model = m;
		front = Vector3(0, 0, 1);
		right = Vector3(1, 0, 0);
		angle = 0;
		pitch = 0;
		maxSide = size.x > size.z ? size.x : size.z;
	}
	Vector3 getMin() {
		return position - Vector3(maxSide, maxSide, maxSide) * 0.5;
	}
	Vector3 getMax() {
		return position + Vector3(maxSide, maxSide, maxSide) * 0.5;
	}
	std::vector<Vector3> getVertices() {
		// only gets 4 vertices for now
		// doesn't account for pitch
		std::vector<Vector3> vertices;
		Vector3 halfSize = size * 0.5;
		vertices.push_back(position + front * halfSize.z + right * halfSize.x + Vector3(0, halfSize.y, 0));
		vertices.push_back(position + front * halfSize.z - right * halfSize.x + Vector3(0, halfSize.y, 0));
		vertices.push_back(position - front * halfSize.z + right * halfSize.x + Vector3(0, halfSize.y, 0));
		vertices.push_back(position - front * halfSize.z - right * halfSize.x + Vector3(0, halfSize.y, 0));

		return vertices;
	}
	void renderBoundingBox();
};
