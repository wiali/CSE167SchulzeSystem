#include "BezierCurve.h"

BezierCurve::BezierCurve() {}
BezierCurve::BezierCurve(Vector3 cp1, Vector3 cp2, Vector3 cp3, Vector3 cp4)
{
	this->cp1 = cp1;
	this->cp2 = cp2;
	this->cp3 = cp3;
	this->cp4 = cp4;
}

Vector3 BezierCurve::getPoint(float t)
{
	//https://piazza.com/class/iey9l011ui55cs?cid=371

	float n = 1.0 - t;

	Vector3 retVec = (cp1 * (n * n * n)) +
		(cp2 * (t * n * n * 3)) +
		(cp3 * (t * t * n * 3)) +
		(cp4 * (t * t * t));
	
	return retVec;

	//return Vector3();
}