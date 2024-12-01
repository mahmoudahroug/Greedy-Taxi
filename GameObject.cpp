#include "GameObject.h"
#include <glut.h>
void GameObject::renderBoundingBox() {
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(angle, 0, 1, 0);
	glScalef(size.x, size.y, size.z);
	glutWireCube(1);
	glPopMatrix();
}
void GameObject::init(Vector3 pos, Vector3 s, int a, char* m) {
	model.Load(m);
	position = pos;
	size = s;
	angle = a;
	rotate(angle * 3.14159f / 180.0f);
}
void GameObject::render() {
	//glPushMatrix();
	//glTranslatef(position.x, position.y, position.z);
	//glScalef(size.x, size.y, size.z);
	//glRotatef(angle, 0, 1, 0);
	//glutSolidCube(1);
	//glutSolidCube(1);
	//glScalef(5, 5, 5);
	////model.render();
	//glPopMatrix();
	renderBoundingBox();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(angle, 0, 1, 0);
	glScalef(size.x, size.y, size.z);
	//glScalef(0.02, 0.02, 0.02);
	model.Draw();
	glPopMatrix();

}
void GameObject::rotate(float rad) {
	float cosA = cos(rad);
	float sinA = sin(rad);
	//float newX = front.x * cosA - front.z * sinA;
	//float newZ = front.x * sinA + front.z * cosA;

	// front -> (sinA, 0, cosA) (no y component / incline)
	front = Vector3(sinA, front.y, cosA);
	right = Vector3(front.z, front.y, -front.x);
	// for incline
	// cosB = cos (pitch); sinB = sin(pitch)
	// front -> (cosB sinA, sinB , cosB cosA)
}
