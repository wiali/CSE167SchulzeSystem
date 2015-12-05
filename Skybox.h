#pragma once
#include "Drawable.h"
#include "Texture.h"
#include "BezierCurve.h"


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
class Skybox : public Drawable
{
public:

	Skybox(float);
	~Skybox();

	float size;
	Texture *back;
	Texture *base;
	Texture *front;
	Texture *left;
	Texture *right;
	Texture *top;

	Texture *logo;

	void draw(Matrix4 C);
	void update();
	void drawBezierCurve(BezierCurve);
	void getBZPoints(BezierCurve bc1, BezierCurve bc2, BezierCurve bc3, BezierCurve bc4);
	void drawFlag();

	Vector3 bezierPoints[100][100];
	Vector3 normals[100][100];
	Vector3 bzPointsTen[20][20];
};