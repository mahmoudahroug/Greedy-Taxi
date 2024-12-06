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
void GameObject::init(Vector3 pos, Vector3 s, Vector3 extraS, int a, char* m) {
	model.Load(m);
	position = pos;
	size = s;
	extraScaling = extraS;
	angle = a;
	rotate(angle * 3.14159f / 180.0f);
}
void GameObject::initcolor(Vector3 pos, Vector3 s, Vector3 colorx, int a, char* m) {
	model.Load(m);
	position = pos;
	size = s;
	angle = a;
	rotate(angle * 3.14159f / 180.0f);
	color = colorx;
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
	renderNormals();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(extraScaling.x, extraScaling.y, extraScaling.z);
	glRotatef(angle, 0, 1, 0);
	//glScalef(0.02, 0.02, 0.02);
	model.Draw();
	glPopMatrix();

}
void GameObject::renderColor() {
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
	glScalef(size.x, size.y, size.z);
	glRotatef(angle, 0, 1, 0);
	glColor3f(color.x,color.y,color.z);
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
std::vector<Vector3> GameObject::getVertices() {
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
void GameObject::renderNormals() {
	// Draw normals
	glDisable(GL_TEXTURE_2D);
	// Disbale lighting if the model is lit
	glDisable(GL_LIGHTING);
	// Draw the normals blue
	glColor3f(0.0f, 0.0f, 1.0f);

	glPushMatrix();
	glTranslatef(position.x, position.y + 5, position.z);
	int scale = 10;
	glScalef(scale, scale, scale);
	// Draw a line between the vertex and the end of the normal
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(front.x, front.y, front.z);
	glEnd();
	glPopMatrix();
	glPushMatrix();

	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(position.x, position.y + 5, position.z);
	glScalef(scale, scale, scale);
	// Draw a line between the vertex and the end of the normal
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(right.x, right.y, right.z);
	glEnd();
	glPopMatrix();
	// Reset the color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	// If the model is lit then renable lighting
	glEnable(GL_LIGHTING);
	
}