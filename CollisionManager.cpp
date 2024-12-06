#include "CollisionManager.h"
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
//using namespace std;
bool CollisionManager::checkCollisionAABB(GameObject& o1, GameObject& o2) {
	Vector3 min1 = o1.getMin();
	Vector3 max1 = o1.getMax();
	Vector3 min2 = o2.getMin();
	Vector3 max2 = o2.getMax();
	
	// use height for y if GameObjects won't have pitch
	return (min1.x <= max2.x && max1.x >= min2.x) &&
		(min1.y <= max2.y && max1.y >= min2.y) &&
		(min1.z <= max2.z && max1.z >= min2.z);
}

bool CollisionManager::checkCollisionOBB(GameObject& o1, GameObject& o2) {
	
	// Implementation for OBB collision detection
	std::vector<Vector3> normals = { o1.front, o1.right, o2.front, o2.right };
	std::vector<Vector3> vertices1 = o1.getVertices();
	std::vector<Vector3> vertices2 = o2.getVertices();

	for (const Vector3& normal : normals)
	{
		float min1 = std::numeric_limits<float>::infinity();
		float max1 = std::numeric_limits<float>::lowest();
		float min2 = std::numeric_limits<float>::infinity();
		float max2 = std::numeric_limits<float>::lowest();
		for (const Vector3& v : vertices1)
		{
			float projection = v.dot(normal);
			min1 = min1 < projection ? min1 : projection;
			max1 = max1 > projection ? max1 : projection;
		}
		for (const Vector3& v : vertices2)
		{
			float projection = v.dot(normal);
			min2 = min2 < projection ? min2 : projection;
			max2 = max2 > projection ? max2 : projection;
		}
		if (max1 < min2 || max2 < min1)
			return false;
	}
	return true;
}
CollisionResult CollisionManager::checkCollision(GameObject& o1, GameObject& o2) {

	// Implementation for OBB collision detection
	std::vector<Vector3> normals = { o1.front, o1.right, o2.front, o2.right };
	std::vector<Vector3> vertices1 = o1.getVertices();
	std::vector<Vector3> vertices2 = o2.getVertices();

	float smallestOverlap = std::numeric_limits<float>::infinity();
	Vector3 collisionNormal;

	for (const Vector3& normal : normals)
	{
		float min1 = std::numeric_limits<float>::infinity();
		float max1 = std::numeric_limits<float>::lowest();
		float min2 = std::numeric_limits<float>::infinity();
		float max2 = std::numeric_limits<float>::lowest();
		for (const Vector3& v : vertices1)
		{
			float projection = v.dot(normal);
			min1 = min1 < projection ? min1 : projection;
			max1 = max1 > projection ? max1 : projection;
		}
		for (const Vector3& v : vertices2)
		{
			float projection = v.dot(normal);
			min2 = min2 < projection ? min2 : projection;
			max2 = max2 > projection ? max2 : projection;
		}
		if (max1 < min2 || max2 < min1)
			return { false, Vector3() };

		float overlap = max1 < max2 ? max1 - min2 : max2 - min1;
		if (overlap < smallestOverlap) {
			smallestOverlap = overlap;
			collisionNormal = normal;
		}
	}
	Vector3 direction = o1.position - o2.position;
	float dot = direction.dot(collisionNormal);
	if (dot < 0) {
		collisionNormal = -collisionNormal;
	}


	return { true, collisionNormal };
}
CollisionResult checkCollision(GameObject& car, Model_3DS& model) {
	
	return { false, Vector3() };
}