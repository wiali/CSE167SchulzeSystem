#pragma once
#include "Group.h"
#include "MatrixTransform.h"
#include "Geode.h"
#include "Sphere.h"
#include "Cube.h"

#define M_PI 3.141592653589793

class Robot : public Group 
{
public:

	float maxX = 0.0;
	float maxY = 0.0;
	float maxZ = 0.0;
	float minX = 0.0;
	float minY = 0.0;
	float minZ = 0.0;
	Vector3 center;
	Matrix4 centerMatrix;
	float radius;

	float cubeSize = 1.0;
	float torsoRadius = 2.0;
	float headRadius = 1.0;
	float angle = 5*M_PI/180.0; //5 degrees
	float angleCounter = 0.0;
	float maxAngle = 90 * M_PI / 180.0; //5 degrees
	float minAngle = -maxAngle;

	int counter = 0;
	
	Sphere* sphereGeode;
	Cube*   cubeGeode;

	Sphere* headGeode;
	Sphere* bodyGeode;
	MatrixTransform* torsoMT;
	MatrixTransform* headMT;
	MatrixTransform* leftLegMT, *rightLegMT;
	MatrixTransform* leftArmMT, *rightArmMT;
	
	Group* root;
	
	Robot(Matrix4);
	void init(Matrix4 C);
	~Robot();
	
	void draw(Matrix4);
	void update();

	void animation1();
	void animation2();



};