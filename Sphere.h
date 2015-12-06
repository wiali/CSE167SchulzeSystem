#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include <iostream>
#include "Drawable.h"
#include "Geode.h"
#include "Color.h"

class Sphere : public Geode
{

public:

	double radius;
	int slices, stacks;

	Sphere(double, int, int);

	void render();
	void renderWire();
	void renderHalo();
	void update(Matrix4);
};

#endif
