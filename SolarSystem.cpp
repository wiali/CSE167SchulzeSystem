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
	planet1Geode = new Sphere(radius1, 50, 50);
	planet2Geode = new Sphere(radius2, 50, 50);
	planet3Geode = new Sphere(radius3, 50, 50);
	planet2_1Geode = new Sphere(radius2, 50, 50);
	
	sunGeode = new Sphere(3.0, 50.0, 50.0);

	//added textures
	planet1Geode->tex = Texture("Mercury.ppm");
	planet1Geode->texNormal = Texture("normalmap.ppm");
	planet1Geode->texHeightMap = Texture("MercuryDisplacement.ppm",1);

	planet2Geode->tex = Texture("Earth.ppm");
	//planet2Geode->initShader();
	planet3Geode->tex = Texture("Mars.ppm");
	planet2_1Geode->tex = Texture("Venus.ppm");
	planet2_1Geode->map = Texture("Ring.ppm");
	sunGeode->tex = Texture("Sun.ppm");

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

	//planet2_1
	temp = C;
	temp.makeTranslate(-orbit2, 0.0, 0.0);
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
	planet1Geode->center = Vector3(planet1MT->M.get(3, 0), planet1MT->M.get(3, 1), planet1MT->M.get(3, 2));

	//planet2
	rotate.identity();
	planet2MT->M = rotate.makeRotateZ(0.0015) * planet2MT->M;
	planet2Geode->angle += 0.0015*180.0 / M_PI;
	planet2Geode->center = Vector3(planet2MT->M.get(3, 0), planet2MT->M.get(3, 1), planet2MT->M.get(3, 2));
	//planet2Geode->center.print("planet 2 center");

	//planet2_1 (will collide with planet2)
	rotate.identity();
	planet2_1MT->M = rotate.makeRotateZ(-0.0035) * planet2_1MT->M;
	planet2_1Geode->angle += -0.0035*180.0/M_PI;
	planet2_1Geode->center = Vector3(planet2_1MT->M.get(3,0), planet2_1MT->M.get(3, 1), planet2_1MT->M.get(3, 2));
	//planet2Geode->center.print("planet 2_1 center");

	//detectCollision(planet2MT, planet2_1MT, planet2Geode, planet2_1Geode);
	detectCollisionBox(planet2MT, planet2_1MT, planet2Geode, planet2_1Geode);

	//planet3
	rotate.identity();
	planet3MT->M = rotate.makeRotateZ(0.002) * planet3MT->M;
	planet3Geode->center = Vector3(planet3MT->M.get(3, 0), planet3MT->M.get(3, 1), planet3MT->M.get(3, 2));

	//update center vector
	center = Vector3(sunMT->M.get(3, 0), sunMT->M.get(3, 1), sunMT->M.get(3, 2));

}

void SolarSystem::animation1()
{
	Matrix4 trans;
	trans.identity();
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
void SolarSystem::detectCollisionBox(MatrixTransform* mt1, MatrixTransform* mt2, Geode* gOne, Geode* gTwo)
{
	radius = radius2;
	float Ax = mt1->M.get(3, 0); //printf("Ax: %f", Ax);
	float Ay = mt1->M.get(3, 1);
	float Az = mt1->M.get(3, 2);
	float AxMin = min(Ax - radius, Ax + radius);
	float AyMin = min(Ay - radius, Ay + radius);
	float AzMin = min(Az - radius, Az + radius);
	float AxMax = max(Ax - radius, Ax + radius);
	float AyMax = max(Ay - radius, Ay + radius);
	float AzMax = max(Az - radius, Az + radius);

	float Bx = mt2->M.get(3, 0);
	float By = mt2->M.get(3, 1);
	float Bz = mt2->M.get(3, 2);
	float BxMin = min(Bx - radius, Bx + radius);
	float ByMin = min(By - radius, By + radius);
	float BzMin = min(Bz-radius, Bz + radius);
	float BxMax = max(Bx - radius, Bx + radius);
	float ByMax = max(By - radius, By + radius);
	float BzMax = max(Bz - radius, Bz + radius);	

	//detect if bounding boxes intersect
	if( (AxMin < BxMax) && (AxMax > BxMin) &&
	    (AyMin < ByMax) && (AyMax > ByMin) &&
		(AzMin < BzMax) && (AzMax > BzMin)) 
	{
		printf("planets collided!!!\n");
		//set change wireframe color to be red
		gOne->wireframeColor = Vector3(1.0, 0.0, 0.0);
		gTwo->wireframeColor = Vector3(1.0, 0.0, 0.0);
	} else {
		//blue
		gOne->wireframeColor = Vector3(0.0, 0.0, 1.0);
		gTwo->wireframeColor = Vector3(0.0, 0.0, 1.0);
	}

}