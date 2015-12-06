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

	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
}
void Sphere::render()
{
	if (tex.name == "Sun.ppm")
	  glDisable(GL_LIGHTING);
	//glColor3f(1.0, 0.0, 0.0);
	tex.bind();
	gluSphere(sphere, radius, slices, stacks);
	tex.unbind();
	if (tex.name == "Sun.ppm")
	  glEnable(GL_LIGHTING);
	//glutSolidSphere(radius, slices, stacks);
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

void Sphere::renderOrbit()
{
	if (tex.name == "Sun.ppm")
	{
		GLUquadric * orbit = gluNewQuadric();
		gluQuadricDrawStyle(orbit, GLU_FILL);
		gluQuadricTexture(orbit, GL_TRUE);
		gluQuadricNormals(orbit, GLU_SMOOTH);
		glColor3f(1.0, 0.0, 0.0);
		glutSolidTorus(.03, 13.55, 5, 50);
		glutSolidTorus(.03, 9.10, 5, 50);
		glutSolidTorus(.03, 18.2, 5, 50);
	}
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


