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