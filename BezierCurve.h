#pragma once

#include "Vector3.h"
#include "Texture.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
class BezierCurve {
public:
	Vector3 cp1;
	Vector3 cp2;
	Vector3 cp3;
	Vector3 cp4;

	BezierCurve();

	BezierCurve(Vector3 cp1, Vector3 cp2, Vector3 cp3, Vector3 cp4);

	Vector3 getPoint(float);
};