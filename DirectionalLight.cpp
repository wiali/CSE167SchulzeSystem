#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light() {
	diffuseColor = Color(1.0, 1.0, 1.0);
	specularColor = Color(1.0, 1.0, 1.0);
	//position = Vector4(1.0, 1.0, 1.0, 0);

	//setup directional light
	Vector4 dirlightPos(0.0, 0.0, 5.0, 0.0);
	position = dirlightPos;
	constantAttenuation = 1.0;
	//linearAttenuation = 0.3;
	//quadraticAttenuation = 0.00;
}

DirectionalLight::~DirectionalLight() {}
void DirectionalLight::draw(Matrix4 mat) {}
void DirectionalLight::update() {}