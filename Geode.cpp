#include "Geode.h"
#include "Globals.h"

void Geode::draw(Matrix4 C) 
{
	/*	? Set ModelView matrix for current render
	? Call render()*/
	//setmodelview(C)
	//render(myObject)
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	//glLoadMatrixf(C.ptr());
	glMultMatrixf(C.ptr());

	render();

	glPopMatrix(); //?

}

void Geode::update() {}
void Geode::render()
{
}

