#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include <list>

#include "glee.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Node {
public:
	Node();
	~Node();

	Vector3 center;
	float radius;

	Matrix4 centerMatrix;

	virtual void draw(Matrix4 C) = 0;
	virtual void update(Matrix4 C) = 0;
	//virtual void drawWireSphere(Matrix4 C);
};