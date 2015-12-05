#include "MatrixTransform.h"

MatrixTransform::MatrixTransform() : Group() 
{
	M.identity();
}
MatrixTransform::MatrixTransform(Matrix4 mat) : Group() {
	this->M = mat;
}
MatrixTransform::~MatrixTransform() {}
 
void MatrixTransform::draw(Matrix4 C) 
{
	/* Multiplies Matrix4 M with Matrix4 C In what order??
	Passes resulting Matrix4 down to children 
	Group::draw(...)*/
	Matrix4 newC = C * M;
	Group::draw(newC);

}
void MatrixTransform::update() {}