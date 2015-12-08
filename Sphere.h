#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include <iostream>
#include "Drawable.h"
#include "Geode.h"
#include "Color.h"
#include "Texture.h"

class Sphere : public Geode
{

public:
	GLUquadric * sphere = NULL;
	GLUquadric * disk = NULL;
	Shader * shader;
	double radius;
	int slices, stacks;
	Texture tex;
	Texture map;
	double orbit;
	Sphere(double, int, int);

	void render();
	void initShader();
	void renderWire();
	void renderHalo();
	void renderOrbit();
	void renderDisk();
	void update(Matrix4);
};

#endif
