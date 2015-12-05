#include "Sphere.h"
#include "Globals.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks)
{
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}
void Sphere::render()
{
	glColor3f(0.0, 0.0, 1.0);
	glutSolidSphere(radius, slices, stacks);
	glColor3f(1.0, 1.0, 1.0);
	if (Globals::showBoundingSpheres)
		glutWireSphere(radius, 15, 15);

}
void Sphere::update(Matrix4 C)
{
}
/*
void Sphere::draw(DrawData& data)
{
material.apply();

glMatrixMode(GL_MODELVIEW);

glPushMatrix();
glMultMatrixf(toWorld.ptr());

glutSolidSphere(radius, slices, stacks);

glPopMatrix();
}

void Sphere::bounce(float radians)
{

}

void Sphere::update(UpdateData& data)
{
//
}*/


