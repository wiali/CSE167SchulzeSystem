#include "House.h"
#include "Cube.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "Vector3.h"
//#include "Vector4.h"
#include "math.h"
#include "Globals.h"

House::House() 
{
}

House::House(float size) : Drawable()
{
	this->size = size;
}

House::~House(void)
{
}


void House::draw(DrawData& data)
{
	float halfSize = size / 2.0;

	//Apply the material properties
	//From here forward anything drawn will be drawn with this material
	material.apply();

	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);

	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	// This data structure defines a simple house

	int nVerts = 42;    // your vertex array needs to have this many entries

						// These are the x,y,z coordinates of the vertices of the triangles
	float vertices[] = {
		-4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
		-4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
		4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
		4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
		4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
		-4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face

		-20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
		-4,4,4, 4,4,4, 0,8,4,                       // front attic wall
		4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
		-4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
		4,4,-4, -4,4,-4, 0,8,-4 };                   // rear attic wall

													 // These are the RGB colors corresponding to the vertices, in the same order
	float colors[] = {
		1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
		0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
		1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
		0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
		0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
		0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue

		0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
		0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
		1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
		0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
		0,0,1, 0,0,1, 0,0,1, };              // rear attic wall is red

											 // The index data stores the connectivity of the triangles; 
											 // index 0 refers to the first triangle defined above
	int indices[] = {
		0,2,3,    0,1,2,      // front face
		4,6,7,    4,5,6,      // left face
		8,10,11,  8,9,10,     // back face
		12,14,15, 12,13,14,   // right face
		16,18,19, 16,17,18,   // top face
		20,22,23, 20,21,22,   // bottom face

		24,26,27, 24,25,26,   // grass
		28,29,30,             // front attic wall
		31,33,34, 31,32,33,   // left slope
		35,37,38, 35,36,37,   // right slope
		39,40,41 };            // rear attic wall

	//Make house!
	//Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
	//These are special calls that 'freeze' many internal states of OpenGL.
	//Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
	//As a good habit, only call glBegin just before you need to draw, and call end just after you finish

	//Loop thru to use array to draw house
	//Set lighting to off to match results
	glDisable(GL_LIGHTING);
	glBegin(GL_TRIANGLES);

	int index;
	float color1, color2, color3;
	float vertex1, vertex2, vertex3;

	for (int i = 0; i < 60; i++) {
		index = indices[i];
		color1 = colors[index * 3];
		color2 = colors[(index * 3) + 1];
		color3 = colors[(index * 3) + 2];

		glColor3f(color1, color2, color3);

		vertex1 = vertices[index * 3];
		vertex2 = vertices[(index * 3) + 1];
		vertex3 = vertices[(index * 3) + 2];

		glVertex3f(vertex1, vertex2, vertex3);
	}
	glEnd();

	glEnd();

	//The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
	//glutSolidCube(size);

	//Pop the save state off the matrix stack
	//This will undo the multiply we did earlier
	glPopMatrix();
}

void House::rasterDraw() {
	int nVerts = 42;    // your vertex array needs to have this many entries

						// These are the x,y,z coordinates of the vertices of the triangles
	float vertices[] = {
		-4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
		-4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
		4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
		4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
		4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
		-4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face

		-20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
		-4,4,4, 4,4,4, 0,8,4,                       // front attic wall
		4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
		-4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
		4,4,-4, -4,4,-4, 0,8,-4 };                   // rear attic wall

													 // These are the RGB colors corresponding to the vertices, in the same order
	float colors[] = {
		1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
		0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
		1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
		0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
		0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
		0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue

		0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
		0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
		1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
		0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
		0,0,1, 0,0,1, 0,0,1, };              // rear attic wall is red

											 // The index data stores the connectivity of the triangles; 
											 // index 0 refers to the first triangle defined above
	int indices[] = {
		0,2,3,    0,1,2,      // front face
		4,6,7,    4,5,6,      // left face
		8,10,11,  8,9,10,     // back face
		12,14,15, 12,13,14,   // right face
		16,18,19, 16,17,18,   // top face
		20,22,23, 20,21,22,   // bottom face

		24,26,27, 24,25,26,   // grass
		28,29,30,             // front attic wall
		31,33,34, 31,32,33,   // left slope
		35,37,38, 35,36,37,   // right slope
		39,40,41 };            // rear attic wall

	//stop flashing triangles
	srand(1);

	Globals::rasterizer.clearBuffer();

	int index = -1;	//reset index
	for (int i = 0; i < 60; i+=3) {
		index = indices[i];
		v1.set(vertices[index*3], vertices[index*3 + 1], vertices[index * 3 + 2],1);
		
		index = indices[i+1];
		v2.set(vertices[index * 3], vertices[index * 3 + 1], vertices[index * 3 + 2],1);
		
		index = indices[i+2];
		v3.set(vertices[index * 3], vertices[index * 3 + 1], vertices[index * 3 + 2],1);

		if (Globals::part == 1) {
			Globals::rasterizer.rasterizeVertex(v1);
			Globals::rasterizer.rasterizeVertex(v2);
			Globals::rasterizer.rasterizeVertex(v3);
		}
		else {
			
			//set colors for part4
			n1.set(colors[index * 3], colors[index * 3 + 1], colors[index * 3 + 2]);
			Globals::rasterizer.rasterizeTriangle(v1, v2, v3);
		}
	}

	Globals::rasterizer.display();
}


void House::update(UpdateData& data)
{
	//
}

