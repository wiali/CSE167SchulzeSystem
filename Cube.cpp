#include "Cube.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "Vector4.h"
#include "Rasterizer.h"
#include "math.h"
#include "Globals.h"

Cube::Cube(float size) : Geode()
{
	this->size = size;
}
Cube::~Cube()
{
	//Delete any dynamically allocated memory/objects here
}

void Cube::render()
{
	double scaleY = 1.5;
	glScaled(1.0, scaleY, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(this->size);

	glScaled(1.0, 1.0 / scaleY, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	if (Globals::showBoundingSpheres)
	{
		//diagonal = sqrt(3)* edge size
		float diagonal = sqrt(1.0 + 1.0 + scaleY * scaleY);
		glutWireSphere(diagonal / 2.0, 10, 10);
	}

};
void Cube::update(Matrix4 C) {};


/*void Cube::draw(DrawData& data)
{
float halfSize = size/2.0;

//Apply the material properties
//From here forward anything drawn will be drawn with this material
material.apply();

//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
glMatrixMode(GL_MODELVIEW);

//Push a save state onto the matrix stack, and multiply in the toWorld matrix
glPushMatrix();
glMultMatrixf(toWorld.ptr());

//Make cube!
//Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
//These are special calls that 'freeze' many internal states of OpenGL.
//Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
//As a good habit, only call glBegin just before you need to draw, and call end just after you finish
glBegin(GL_QUADS);

// Draw front face:
glNormal3f(0.0, 0.0, 1.0);
glVertex3f(-halfSize,  halfSize,  halfSize);
glVertex3f( halfSize,  halfSize,  halfSize);
glVertex3f( halfSize, -halfSize,  halfSize);
glVertex3f(-halfSize, -halfSize,  halfSize);

// Draw left side:
glNormal3f(-1.0, 0.0, 0.0);
glVertex3f(-halfSize,  halfSize,  halfSize);
glVertex3f(-halfSize,  halfSize, -halfSize);
glVertex3f(-halfSize, -halfSize, -halfSize);
glVertex3f(-halfSize, -halfSize,  halfSize);

// Draw right side:
glNormal3f(1.0, 0.0, 0.0);
glVertex3f( halfSize,  halfSize,  halfSize);
glVertex3f( halfSize,  halfSize, -halfSize);
glVertex3f( halfSize, -halfSize, -halfSize);
glVertex3f( halfSize, -halfSize,  halfSize);

// Draw back face:
glNormal3f(0.0, 0.0, -1.0);
glVertex3f(-halfSize,  halfSize, -halfSize);
glVertex3f( halfSize,  halfSize, -halfSize);
glVertex3f( halfSize, -halfSize, -halfSize);
glVertex3f(-halfSize, -halfSize, -halfSize);

// Draw top side:
glNormal3f(0.0, 1.0, 0.0);
glVertex3f(-halfSize,  halfSize,  halfSize);
glVertex3f( halfSize,  halfSize,  halfSize);
glVertex3f( halfSize,  halfSize, -halfSize);
glVertex3f(-halfSize,  halfSize, -halfSize);

// Draw bottom side:
glNormal3f(0.0, -1.0, 0.0);
glVertex3f(-halfSize, -halfSize, -halfSize);
glVertex3f( halfSize, -halfSize, -halfSize);
glVertex3f( halfSize, -halfSize,  halfSize);
glVertex3f(-halfSize, -halfSize,  halfSize);

glEnd();

//The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
//glutSolidCube(size);

//Pop the save state off the matrix stack
//This will undo the multiply we did earlier
glPopMatrix();
}*/

/*void Cube::rasterDraw() {
printf("Cube raster draw called\n");
//stop flashing triangles
srand(1);

Globals::rasterizer.clearBuffer();

float cubeSize = size;
float halfSize = cubeSize / 2.0;

Vector4 front1(-halfSize, halfSize, halfSize);
Vector4 front2(halfSize, halfSize, halfSize);
Vector4 front3(halfSize, -halfSize, halfSize);
Vector4 front4(-halfSize, -halfSize, halfSize);
Vector4 left1(-halfSize, halfSize, -halfSize);
Vector4 left2(-halfSize, -halfSize, -halfSize);
Vector4 right1(halfSize, halfSize, -halfSize);
Vector4 right2(halfSize, -halfSize, -halfSize);

if (Globals::part == 1) {
Globals::rasterizer.rasterizeVertex(front1);
Globals::rasterizer.rasterizeVertex(front2);
Globals::rasterizer.rasterizeVertex(front3);
Globals::rasterizer.rasterizeVertex(front4);
Globals::rasterizer.rasterizeVertex(left1);
Globals::rasterizer.rasterizeVertex(left2);
Globals::rasterizer.rasterizeVertex(right1);
Globals::rasterizer.rasterizeVertex(right2);
}
else {

//draw 8 quads as 12 triangles
//set normals to use for color in part4

n1.set(0.0, 0.0, 1.0);
Globals::rasterizer.rasterizeTriangle(front1, front2, front3);
Globals::rasterizer.rasterizeTriangle(front3, front4, front1);

n1.set(1.0, 0.0, 0.0);
Globals::rasterizer.rasterizeTriangle(front1, left1, left2);
Globals::rasterizer.rasterizeTriangle(left2, front4, front1);

n1.set(-1.0, 0.0, 0.0);
Globals::rasterizer.rasterizeTriangle(front2, right1, right2);
Globals::rasterizer.rasterizeTriangle(right2, front3, front2);

n1.set(0.0, 0.0, -1.0);
Globals::rasterizer.rasterizeTriangle(left1, right1, right2);
Globals::rasterizer.rasterizeTriangle(right2, left2, left1);

n1.set(0.0, 1.0, 0.0);
Globals::rasterizer.rasterizeTriangle(front1, front2, right1);
Globals::rasterizer.rasterizeTriangle(right1, left1, front1);

n1.set(0.0, -1.0, 0.0);
Globals::rasterizer.rasterizeTriangle(left2, right2, front3);
Globals::rasterizer.rasterizeTriangle(front3, front4, left2);
}

Globals::rasterizer.display();

}*/

/*void Cube::update(UpdateData& data)
{
//
}

void Cube::spin(float radians)
{
Matrix4 rotation;
rotation.makeRotateY(radians);

toWorld = toWorld * rotation;
}*/

