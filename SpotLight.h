#pragma once

#include "Light.h"
#include "Drawable.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class SpotLight : public Light {

public:
	SpotLight();
	~SpotLight();

	Vector4 direction;

	virtual void draw(DrawData&);
	virtual void update();

};