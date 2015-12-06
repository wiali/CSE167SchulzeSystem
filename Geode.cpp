#include "Geode.h"
#include "Globals.h"

void Geode::draw(Matrix4 C) 
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(C.ptr());
	render();
	glPopMatrix(); //?

	//halo
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(C.ptr());
	renderHalo();//draw halo
	glPopMatrix();

	if (Globals::showBoundingSpheres) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(C.ptr());
		glScalef(1.1, 1.1, 1.1);
		renderWire();
		glPopMatrix();
	}
}

void Geode::update() {}
void Geode::render()
{
}

void Geode::renderWire()
{
}

void Geode::renderHalo()
{
}

