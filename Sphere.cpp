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
	bump = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	//initShader();
}
void Sphere::initShader()
{
		const char * aa = "Sky.vert";
		const char * bb = "Sky.frag";
		shader = new Shader(aa, bb);
}
void Sphere::render()
{
	//glDisable(GL_DEPTH_TEST);
	if (tex.name == "Sun.ppm")
	{
		glDisable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);
	}
	glColor4f(1.0, 1.0, 1.0, 0.0);
	tex.bind();
	gluSphere(sphere, radius, slices, stacks);
	tex.unbind();
	if (tex.name == "Venus.ppm")
	{
		map.bind();
		gluSphere(bump, radius, slices, stacks);
		map.unbind();
	}

	if (tex.name == "Sun.ppm")
	{
		glEnable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
	}
	//glEnable(GL_DEPTH_TEST);
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
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_ONE, GL_ONE);
		glScalef(1.1, 1.1, 1.1);
		//glColor4f(1.0, 1.0, 0.0, 0.5);
		//glutSolidSphere(radius, 50, 50);
		if (tex.name == "Earth.ppm")
		{
			//glDisable(GL_LIGHTING);
			glColor4f(0.0, 0.4, 1.0, 0.7);
			glutSolidSphere(radius+.1, 50, 50);
			//glEnable(GL_LIGHTING);
		}
		if (tex.name == "Mars.ppm")
		{
			glColor4f(1.0, 0.4, 0.4, 0.3);
			glutSolidSphere(radius + .1, 50, 50);
		}
		if (tex.name == "Mercury.ppm")
		{
			glColor4f(1.0, 0.3, 0.3, 0.3);
			glutSolidSphere(radius + .1, 50, 50);
		}
		if (tex.name == "Venus.ppm")
		{
			glColor4f(1.0, 0.2, 0.2, 0.2);
			glutSolidSphere(radius + .1, 50, 50);
		}
		//glutSolidSphere(radius+.25, 50, 50);
		//gluDisk(disk, radius, .5, 50, 50);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}
	//glFlush();
}
void Sphere::renderOrbit()
{
	if (tex.name == "Sun.ppm")
	{
		glDisable(GL_LIGHTING);
		GLUquadric * orbit = gluNewQuadric();
		gluQuadricDrawStyle(orbit, GLU_FILL);
		gluQuadricTexture(orbit, GL_TRUE);
		gluQuadricNormals(orbit, GLU_SMOOTH);
		glColor3f(1.0, 0.0, 0.0);
		glutSolidTorus(.03, 13.55, 5, 50);
		glutSolidTorus(.03, 9.10, 5, 50);
		glutSolidTorus(.03, 18.2, 5, 50);
		glEnable(GL_LIGHTING);
	}
}
void Sphere::renderDisk() // for rings
{ /*
	if (tex.name != "Sun.ppm")
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDisable(GL_LIGHTING);
		float incr = (float)(2 * 3.14 / 25);
		disk = gluNewQuadric();
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (tex.name == "Merc.ppm")
		{
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(1.0, 1.0, 1.0);
			glVertex2f(0.0f, 0.0f);
			glColor4f(0.1, 0.1, 0.1, 0.1);
			for (int i = 0; i < 25; i++)
			{
				float angle = incr * i;

				float x = (float)cos(angle) * .75;
				float y = (float)sin(angle) * .75;

				glVertex2f(x, y);
			}
			glVertex2f(.75, 0.0f);
			glEnd();
		}
		if (tex.name == "Venus.ppm")
		{
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(1.0, 5.0, 5.0);
			glVertex2f(0.0f, 0.0f);
			glColor4f(0.1, 0.1, 0.1, 0.1);
			for (int i = 0; i < 25; i++)
			{
				float angle = incr * i;

				float x = (float)cos(angle) * 1.2;
				float y = (float)sin(angle) * 1.2;

				glVertex2f(x, y);
			}
			glVertex2f(1.2, 0.0f);
			glEnd();
		}
		map.bind();
		//gluDisk(disk, 1, 1.4, 50, 50);
		//glutSolidTorus(.03, 1.55, 5, 50);
		map.unbind();
		//glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
	}*/
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


