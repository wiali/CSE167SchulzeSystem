#pragma once

#include "Light.h"
#include "Drawable.h"

class DirectionalLight : public Light {

public:
	DirectionalLight();
	~DirectionalLight();

	Vector4 direction;

	virtual void draw(Matrix4 c);
	virtual void update();
	
};