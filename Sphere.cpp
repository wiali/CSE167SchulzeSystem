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
	//this->wireframeColor = Color(0.0, 0.0, 1.0);
}
void Sphere::render()
{

	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(radius, slices, stacks);
	//this->center.print("center");
	
}
void Sphere::renderWire() 
{
	glColor3f(0.0, 0.0, 1.0);
	glColor3f(this->wireframeColor[0], this->wireframeColor[1], this->wireframeColor[2]);
	glutWireSphere(radius, 15, 15);
}
void Sphere::renderHalo() 
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glScalef(1.1, 1.1, 1.1); 
	glColor4f(1.0, 1.0, 0.0, 0.5);
	glutSolidSphere(radius, 50, 50);
	glDisable(GL_BLEND);
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


