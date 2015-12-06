#pragma once
#include "Group.h"

class MatrixTransform : public Group {
public:
	Matrix4 M;
	/*
	Multiplies Matrix4 M with Matrix4 C
	 In what order?
	 Passes resulting Matrix4 down to children with Group::draw(...)
	*/
	Vector3 center;
	MatrixTransform();
	MatrixTransform(Matrix4 mat);
	~MatrixTransform();
	void draw(Matrix4 C);
	void update();

};