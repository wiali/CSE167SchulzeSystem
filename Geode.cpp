#include "Geode.h"
#include "Globals.h"

void Geode::draw(Matrix4 C) 
{
	if (Globals::showHaloEffect) // halo
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(C.ptr());
		renderHalo();//draw halo
		glPopMatrix();
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(C.ptr());
	render();
	//renderDisk();
	glPopMatrix(); //?
	if (Globals::showOrbit) // orbits
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(C.ptr());
		glScalef(1.1, 1.1, 1.1);
		renderOrbit();//draw orbits
		glPopMatrix();
	}
	if (Globals::showBoundingSpheres) // bounding boxes
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		Matrix4 t;
		t.identity();
		Matrix4 id;
		//transform matrix to axis aligned
		t = id.makeTranslate(this->center);
		//t.print("t");
		glMultMatrixf(t.ptr());
		glScalef(1.1, 1.1, 1.1);
		renderWire();	
		glPopMatrix();
	}
}
void Geode::update() {}
void Geode::initShader()
{
}
void Geode::render()
{
}
void Geode::renderWire()
{
}
void Geode::renderHalo()
{
}
void Geode::renderOrbit()
{
}
void Geode::renderDisk()
{
}

