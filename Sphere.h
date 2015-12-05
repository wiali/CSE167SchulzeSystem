#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include <iostream>
#include "Drawable.h"
#include "Geode.h"

class Sphere : public Geode
{

public:

	double radius;
	int slices, stacks;

	Sphere(double, int, int);

	void render();
	void update(Matrix4);
};

#endif
