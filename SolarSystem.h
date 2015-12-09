#pragma once
#pragma once
#include "Group.h"
#include "MatrixTransform.h"
#include "Geode.h"
#include "Sphere.h"
#include "Cube.h"

#define M_PI 3.141592653589793

class SolarSystem : public Group
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
	float angle = 5 * M_PI / 180.0; //5 degrees
	float angleCounter = 0.0;
	float maxAngle = 90 * M_PI / 180.0; //5 degrees
	float minAngle = -maxAngle;

	float radius1 = 0.5;
	float radius2 = 1.0;
	float radius3 = 0.3;

	float orbit1 = 10.0;
	float orbit2 = 15.0;
	float orbit3 = 20.0;

	//for collision detection
	float distX = 0.0;
	float distY = 0.0;
	float distZ = 0.0;

	int counter = 0;

	Sphere* sphereGeode;
	Cube*   cubeGeode;

	Sphere* headGeode;
	Sphere* bodyGeode;
	Sphere* sunGeode;
	Sphere* planet1Geode;
	Sphere* planet2Geode;
	Sphere* planet3Geode;
	Sphere* planet2_1Geode;

	///MatrixTransform* torsoMT;
	MatrixTransform* headMT;
	MatrixTransform* leftLegMT, *rightLegMT;
	MatrixTransform* leftArmMT, *rightArmMT;

	MatrixTransform* sunMT;
	MatrixTransform* planet1MT;
	MatrixTransform* planet2MT;
	MatrixTransform* planet3MT;

	MatrixTransform* planet2_1MT;
	Group* root;

	SolarSystem(Matrix4);
	void init(Matrix4 C);
	~SolarSystem();

	void draw(Matrix4);
	void update();

	void animation1();
	void detectCollision(MatrixTransform* mt1, MatrixTransform* mt2, Geode*, Geode*);
	void detectCollisionBox(MatrixTransform * mt1, MatrixTransform * mt2, Geode * gOne, Geode * gTwo);
	void drawBoundingSpheres(Matrix4 C);
	void animation2();



};