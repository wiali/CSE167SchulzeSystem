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

	// sphere constructor
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
}
void Sphere::initShader()
{
	if (tex.name == "Earth.ppm")
	{
		const char * aa = "Sample.vert";
		const char * bb = "Sample.frag";
		shader = new Shader(aa, bb);
	}
}
void Sphere::render()
{
	if (tex.name == "Sun.ppm")
	  glDisable(GL_LIGHTING);
	/*if (tex.name == "Earth.ppm")
	{
		shader->bind();
		tex.bind();
		glScalef(1.1, 1.1, 1.1);
		glColor4f(1.0, 1.0, 1.0, 0.2);
		glutSolidSphere(radius, slices, stacks);
		shader->unbind();
		tex.unbind();
		glFlush();
	}*/
	glColor4f(1.0, 1.0, 1.0, 0.0);
	tex.bind();
	gluSphere(sphere, radius, slices, stacks);
	tex.unbind();
	if (tex.name == "Venus.ppm")
	{
		renderDisk();
	}
	if (tex.name == "Sun.ppm")
	  glEnable(GL_LIGHTING);
}	
void Sphere::renderWire() 
{
	glScalef(1.01, 1.01, 1.01);
	//glColor3f(0.0, 0.0, 1.0);
	glColor3f(this->wireframeColor[0], this->wireframeColor[1], this->wireframeColor[2]);
	glutWireSphere(radius, 15, 15);	
}
void Sphere::renderHalo() 
{
	if (tex.name != "Sun.ppm")
	{
		disk = gluNewQuadric();
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_ONE, GL_ONE);
		glScalef(1.1, 1.1, 1.1);
		//glColor4f(1.0, 1.0, 0.0, 0.5);
		//glutSolidSphere(radius, 50, 50);
		if (tex.name == "Earth.ppm")
		{
			glColor4f(0.0, 0.4, 1.0, 0.3);
			gluDisk(disk, radius, 1, 50, 50);
		}
		if (tex.name == "Mars.ppm")
			glColor4f(1.0, 0.4, 0.4, 0.3);
		if (tex.name == "Mercury.ppm")
			glColor4f(1.0, 0.3, 0.3, 0.3);
		if (tex.name == "Venus.ppm")
		{
			glColor4f(1.0, 0.2, 0.2, 0.2);
			gluDisk(disk, radius, 1, 50, 50);
		}
		//glutSolidSphere(radius+.25, 50, 50);
		gluDisk(disk, radius, .5, 50, 50);
		glDisable(GL_BLEND);
	}
	glFlush();
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
void Sphere::renderDisk()
{
	disk = gluNewQuadric();
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	map.bind();
	//gluDisk(disk, 1, 1.4, 50, 50);
	//glutSolidTorus(.03, 1.55, 5, 50);
	map.unbind();
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


