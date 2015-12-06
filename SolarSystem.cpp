#ifdef _WIN32
#include <windows.h>
#endif

#include "SolarSystem.h"
#include "Globals.h"


SolarSystem::SolarSystem(Matrix4 C) : Group() {
	//initialize robot at position specified by C
	init(C);
	//radius
	radius = torsoRadius + 2 * cubeSize;
	//set center
	center = Vector3(C.get(3, 0), C.get(3, 1), C.get(3, 2));
	//center.print("center vector");
}
void SolarSystem::init(Matrix4 C)
{
	//root Group
	root = new Group();

	sphereGeode = new Sphere(1.0, 10, 10);
	
	//geodes
	planet1Geode = new Sphere(radius1, 10, 10);
	planet2Geode = new Sphere(radius2, 10, 10);
	planet3Geode = new Sphere(radius3, 10, 10);
	planet2_1Geode = new Sphere(radius2, 10, 10);
	
	sunGeode = new Sphere(3.0, 10.0, 10.0);

	cubeGeode = new Cube(cubeSize);
	
	//transformations
	Matrix4 temp;

	//sun
	temp = C;
	sunMT = new MatrixTransform(temp);

	//planet1
	temp = C;
	temp.makeTranslate(orbit1, 0.0, 0.0);
	planet1MT = new MatrixTransform(temp);
	planet1MT->addChild(planet1Geode);
	sunMT->addChild(planet1MT);

	//planet2
	temp = C;
	temp.makeTranslate(orbit2, 0.0, 0.0);
	planet2MT = new MatrixTransform(temp);
	planet2MT->addChild(planet2Geode);
	sunMT->addChild(planet2MT);

	//planet2
	temp = C;
	temp.makeTranslate(-orbit2, 0.1, 0.0);
	planet2_1MT = new MatrixTransform(temp);
	planet2_1MT->addChild(planet2_1Geode);
	sunMT->addChild(planet2_1MT);

	//planet3
	temp = C;
	temp.makeTranslate(orbit3, 0.0, 0.0);
	planet3MT = new MatrixTransform(temp);
	planet3MT->addChild(planet3Geode);
	sunMT->addChild(planet3MT);
	
	//add child of root
	root->addChild(sunMT);

	//add cube geode as child of all limbs
	sunMT->addChild(sunGeode);

}

SolarSystem::~SolarSystem()
{
	delete root;
}

void SolarSystem::draw(Matrix4 C)
{

	this->root->draw(C);

}
//update angle
//find pivot point
//translate from pivot point to origin
//rotate at origin
//translate back to pivot point
void SolarSystem::update()
{
	angleCounter += angle;

	if (angleCounter >= maxAngle || angleCounter <= minAngle) {
		angle = -angle;
	}
	float tempAngle = angleCounter*180.0 / M_PI;
	//printf("angle: %f\n", tempAngle);

	//planet1
	Matrix4 rotate;
	planet1MT->M = rotate.makeRotateZ(0.001) * planet1MT->M;

	//planet2
	rotate.identity();
	planet2MT->M = rotate.makeRotateZ(0.0015) * planet2MT->M;

	//planet2_1 (will collide with planet2)
	rotate.identity();
	planet2_1MT->M = rotate.makeRotateZ(-0.0015) * planet2_1MT->M;

	detectCollision(planet2MT, planet2_1MT, planet2Geode, planet2_1Geode);

	//planet3
	rotate.identity();
	planet3MT->M = rotate.makeRotateZ(0.002) * planet3MT->M;

	//update center vector
	center = Vector3(sunMT->M.get(3, 0), sunMT->M.get(3, 1), sunMT->M.get(3, 2));

}

void SolarSystem::animation1()
{
	Matrix4 trans;
	trans.identity();
	//turn
	/*if (counter == 210) {
		counter = 0;
		torsoMT->M = torsoMT->M * trans.makeRotateY(90 * M_PI / 180.0);
		trans.identity();
	}
	//move
	torsoMT->M = torsoMT->M * trans.makeTranslate(0.0, 0.0, -.2);
	counter += 1;*/
}

void SolarSystem::detectCollision(MatrixTransform* mt1, MatrixTransform* mt2, Geode* gOne, Geode* gTwo)
{
	distX = abs(mt1->M.get(3, 0) - mt2->M.get(3, 0));
	distY = abs(mt1->M.get(3, 1) - mt2->M.get(3, 1));
	distZ = abs(mt1->M.get(3, 2) - mt2->M.get(3, 2));

	//printf("distance x: %f, y: %f, z: %f \n", distanceX, distanceY, distanceZ);
	float distance = sqrt(distX*distX + distY*distY + distZ*distZ);

	if (distance <= (radius2 + radius2)) {
		printf("planets collided!!!\n");
		printf("distance X %f, distanceY %f, distZ %f \n", distX, distY, distZ);
		printf("distance %f \n", distance);
		//set change wireframe color to be red
		gOne->wireframeColor = Vector3(1.0, 0.0, 0.0);
		gTwo->wireframeColor = Vector3(1.0, 0.0, 0.0);

	}
	else 
	{//blue
		gOne->wireframeColor = Vector3(0.0, 0.0, 1.0);
		gTwo->wireframeColor = Vector3(0.0, 0.0, 1.0);
	}

}