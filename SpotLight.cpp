#include "SpotLight.h"

SpotLight::SpotLight() : Light() {

	//setup spot light
	Vector4 spotlightPos(0.0, 5.0, 10.0, 1.0);
	position = spotlightPos;
	diffuseColor = Color(1.0, 1.0, 1.0);
	specularColor = Color(1.0, 1.0, 1.0);
	ambientColor = Color(1.0, 1.0, 1.0);
	constantAttenuation = 1.0;
	linearAttenuation = 0.0;
	quadraticAttenuation = 0.00;
	cutoff = 15.0;
	exponent = 1.0;

	Matrix4 temp;
	temp = temp.makeTranslate(position.toVector3());
	toWorld = toWorld * temp;
}

SpotLight::~SpotLight() {}
void SpotLight::draw(DrawData&) {
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());
	//toWorld.print("spotlight toworld");
	glColor3f(1.0, 1.0, 1.0); 
	glutSolidSphere(0.5,20.0,20.0);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);

}
void SpotLight::update() {}