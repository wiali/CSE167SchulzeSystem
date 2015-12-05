#pragma once
#include "Vector3.h"

class Plane {
public:
	Plane();
	~Plane();

	Vector3 point, normal;

	void setNormalAndPoint(Vector3& n, Vector3& p)
	{
		normal = n;
		normal = normal.normalize();
		point = p;
	}

	float distance(Vector3& p) 
	{ 
		Vector3 distance = p - point; 
		return distance.dot(normal);
	}

	void set3Points(Vector3& v1, Vector3& v2, Vector3& v3) 
	{
		Vector3 aux1, aux2;

		aux1 = v1 - v2;
		aux2 = v3 - v2;

		normal = aux2 * aux1;

		normal = normal.normalize();

		point = v2;
	}
};
