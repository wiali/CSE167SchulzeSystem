#ifdef _WIN32
#include <windows.h>
#endif

#include "Rasterizer.h"
#include "Globals.h"
#include "OBJObject.h"
#include "Window.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define M_PI 3.1415926

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static float* zbuffer = new float[window_width * window_height];
static float zValue;

/*float Rasterizer::alpha = 0.0;
float Rasterizer::beta = 0.0;
float Rasterizer::gamma = 0.0;*/

using namespace std;

Rasterizer::Rasterizer() {
	//set D matrix
	D.set(window_width / 2.0, 0, 0, 0,
		0, window_height / 2.0, 0, 0,
		0, 0, 1.0 / 2.0, 0,
		window_width / 2.0, window_height / 2.0, 1.0 / 2.0, 1);

	//toDraw = &Globals::cube;
	
}
Rasterizer::~Rasterizer() {}

void loadData()
{
	// put code to load data model here
}

// Clear frame buffer
void Rasterizer::clearBuffer()
{
	Color clearColor = { 0.0, 0.0, 0.0 };   // clear color: black

	for (int i = 0; i<window_width*window_height; ++i)
	{
		pixels[i * 3] = clearColor[0];
		pixels[i * 3 + 1] = clearColor[1];
		pixels[i * 3 + 2] = clearColor[2];

		//clear zbuffer
		zbuffer[i] = 1.0;
	}
}

// Draw a point into the frame buffer
void Rasterizer::drawPoint(int x, int y, float r, float g, float b)
{
	//printf("Drawpoint called\n");
	if ( (x > window_width) || (x < 0) || (y > window_height) || (y < 0))
		return;
	
	int offset = y*window_width * 3 + x * 3;
	//Check was within the index of pixels(i.e.between 0 and height*width * 3)
	if (offset > window_height*window_width * 3 || offset < 0)
		return;

	pixels[offset] = r;
	pixels[offset + 1] = g;
	pixels[offset + 2] = b;
}

void Rasterizer::makeProspectiveProjectionMatrix(float fov, float aspect, float nr, float fr)
{
	//convert field of view to radians
	float FOV = (fov / 180.0)*M_PI;

	P.set( 1.0 / (aspect*(tan(FOV / 2.0))),0,0,0,
		   0, 1.0 / (tan(FOV / 2.0)), 0, 0,
		   0, 0, (nr+fr) / (nr-fr), -1, 
		   0, 0, (2.0*nr*fr) / (nr-fr), 0);
}

void Rasterizer::makeViewportMatrix(float x, float y)
{
	D.set(x / 2.0, 0, 0, 0,
		  0, y / 2.0, 0, 0,
		  0, 0, 1.0 / 2.0, 0,
		  x / 2.0, y / 2.0, 1.0 / 2.0, 1);

}

Vector4 Rasterizer::rasterizeVertex(Vector4& V)
{
	//M * p  -> world space
	// C^-1 * M * p -> camera space
	//Dehomogenize
	// P * C^-1 * M * p -> clip space
	// D * P * C^-1 * M * p -> image space
	//
	V  = toDraw->toWorld * V;
	V = Globals::camera.getInverseMatrix() * V;
	V = P * V;
	V = V.dehomogenize();
	V = D * V;
	
	if ((int)V[0] <= window_width && (int)V[1] <= window_height && (int)V[0] >= 0 && (int)V[1] >= 0)
			drawPoint((int)V[0], (int)V[1], 1.0, 1.0, 1.0);
	
	
	return V;
}

void Rasterizer::draw()
{

}

void  Rasterizer::rasterizeTriangle(Vector4 a, Vector4 b, Vector4 c)
{

	// Add code to rasterize a triangle
	//rasterize three vertices of triangle to get pixel coordinates
	a = toDraw->toWorld * a;
	a = Globals::camera.getInverseMatrix() * a;
	a = P * a;
	a = a.dehomogenize();
	a = D * a;

	b = toDraw->toWorld * b;
	b = Globals::camera.getInverseMatrix() * b;
	b = P * b;
	b = b.dehomogenize();
	b = D * b;

	c = toDraw->toWorld * c;
	c = Globals::camera.getInverseMatrix() * c;
	c = P * c;
	c = c.dehomogenize();
	c = D * c;

	Vector3 x = a.toVector3();
	Vector3 y = b.toVector3();
	Vector3 z = c.toVector3();

	//Compute a 2D bounding box
	//use min x and min y as one corner and max x and max y as other corner
	int minX = min(min(x[0], y[0]), z[0]);
	int minY = min(min(x[1], y[1]), z[1]);
	int maxX = max(max(x[0], y[0]), z[0]);
	int maxY = max(max(x[1], y[1]), z[1]);
	
	//Make sure pixel on screen
	minX = max(minX, 0);
	minY = max(minY, 0);
	maxX = min(maxX, window_width - 1);
	maxY = min(maxY, window_height - 1);
	

	R = (float)(rand() % 100) / (100.0);
	G = (float)(rand() % 100) / (100.0);
	B = (float)(rand() % 100) / (100.0);

	if (Globals::part < 5) {
		//Loop through pixels in bounding box
		for (int i = minX; i <= maxX; i++) {
			for (int j = minY; j <= maxY; j++) {
				Vector3 p(i, j, 0);

				if (computeBarycentric(x, y, z, p)) {

					int offset = j*window_width + i;
					
					//Part 2
					if (Globals::part == 2)
					{
						drawPoint(i, j, R, G, B);
					}
					//Part 3 zBuffer
					else if (Globals::part == 3) 
					{
						//if z is less than the z value found in our z buffer at the index of our current pixel
						// AND is greater than 0
						if (zValue < zbuffer[offset] && zValue > 0.0)
						{
							//draw the pixel
							drawPoint(i, j, R, G, B);
							//update zbuffer with z
							zbuffer[offset] = zValue;

						}			
					}
					//Part 4 Per pixel
					else if (Globals::part == 4) {
						
						//Normalize
						toDraw->n1 = toDraw->n1.normalize();
						toDraw->n2 = toDraw->n2.normalize();
						toDraw->n3 = toDraw->n3.normalize();

						//Interpolate the vertices' normals
						Vector3 color(toDraw->n1*alpha + toDraw->n2*beta + toDraw->n3*gamma);

						//Divide 3 normals by 2.0 and add <0.5,0.5,0.5>
						color = color.multiply(1.0 / 2.0);
						color = color.add(Vector3(0.5, 0.5, 0.5));

						R = color[0];
						G = color[1];
						B = color[2];

						//if z is less than the z value found in our z buffer at the index of our current pixel
						// AND is greater than 0
						if (zValue < zbuffer[offset] && zValue > 0.0)
						{
							//draw the pixel
							drawPoint(i, j, R, G, B);
							//update zbuffer with z
							zbuffer[offset] = zValue;

						}
					}

				}
			}
		}
	}

	//Change to use debug mode
	if (Globals::debugMode && Globals::part >= 2) {
		//Drawing bounding box
		printf("Drawing bounding box\n");
		for (int y = minY; y < maxY; y++) {
			int x = minX;
			drawPoint(x, y, 1, .5, .5);
		}
		for (int y = minY; y < maxY; y++) {
			int x = maxX;
			drawPoint(x, y, 1, .2, .2);
		}
		for (int x = minX; x < maxX; x++) {
			int y = minY;
			drawPoint(x, y, 1, .2, .2);
		}
		for (int x = minX; x < maxX; x++) {
			int y = maxY;
			drawPoint(x, y, 1, .2, .2);
		}
	}



}

void  Rasterizer::rasterize()
{
	//printf("in rasterize()\n");
	// Put your main rasterization loop here
	// It should go over the data model and call rasterizeTriangle for every triangle in it

	// example: draw diagonal line:
	/*for (int i = 0; i<min(window_width, window_height); ++i)
	{
		drawPoint(i, i, 1.0, 0.0, 0.0);
	}*/

}

// Called whenever the window size changes
void  Rasterizer::reshape(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;
	delete[] pixels;
	pixels = new float[window_width * window_height * 3];
	delete[] zbuffer;
	zbuffer = new float[window_width * window_height];

	makeViewportMatrix(new_width, new_height);
	makeProspectiveProjectionMatrix(60.0, (float)new_width / (float)new_height, 1.0, 1000.0);
}

void Rasterizer::display()
{
	//engine is on
	//clearBuffer();
	//printf("ClearBuffer called\n");
	//rasterize();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

	//glutSwapBuffers();
}

void keyboard(unsigned char key, int, int)
{
	cerr << "Key pressed: " << key << endl;
}

bool Rasterizer::computeBarycentric(Vector3 a, Vector3 b, Vector3 c, Vector3& p) {
	//printf("Compute barycentric called \n");

	Vector3 v0 = b - a;
	Vector3 v1 = c - a;
	Vector3 v2 = c - b;
	Vector3 v3 = p - b;
	Vector3 v4 = a - c;
	Vector3 v5 = p - c;
	Vector3 v6 = p - a;

	Vector3 normalA = v0.cross(v1);
	Vector3 normalB = v2.cross(v3);
	Vector3 normalC = v4.cross(v5);


	float normalMag = normalA.magnitude()*normalA.magnitude();
	float normalVectorA = normalA.dot(normalB);
	float normalVectorB = normalA.dot(normalC);

	alpha = normalVectorA / normalMag;
	beta = normalVectorB / normalMag;
	gamma = 1 - alpha - beta;

	//Check alpha, beta, and gamma are ALL between 0 and 1
	if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1) {
		//Set zbuffer value
		zValue = a[2] * alpha + b[2] * beta + c[2] * gamma;
		return true;
	}
	else
		return false;
}
