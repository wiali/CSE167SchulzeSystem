#pragma once
#pragma once

#include "Light.h"
#include "Drawable.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class PointLight : public Light {

public:
	PointLight();
	~PointLight();

	Vector4 direction;

	virtual void draw(DrawData&);
	virtual void update();

};