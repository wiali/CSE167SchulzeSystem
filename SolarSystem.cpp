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

	//geodes
	headRadius = 1.0;
	Sphere* sunGeode = new Sphere(torsoRadius, 10.0, 10.0);

	cubeGeode = new Cube(cubeSize);
	//transformations
	Matrix4 temp;

	//torso
	temp = C;
	sunMT = new MatrixTransform(temp);
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
	
	if (Globals::showBoundingSpheres)
	{
		Matrix4 m;
		m.identity();
		m = m * m.makeTranslate(center);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(m.ptr());
		glColor3f(1.0, 1.0, 1.0);
		glutWireSphere(radius, 10, 10);
		glPopMatrix();
	}

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

	//left leg
	Matrix4 tmp;
	leftLegMT->M = tmp.makeTranslate(0.0, torsoRadius, 0.0) * leftLegMT->M;
	Matrix4 rotate;
	leftLegMT->M = rotate.makeRotateX(-angle) * leftLegMT->M;
	leftLegMT->M = tmp.makeTranslate(0.0, -torsoRadius, 0.0) * leftLegMT->M;

	//right leg
	tmp.identity();
	rightLegMT->M = tmp.makeTranslate(0.0, torsoRadius, 0.0) * rightLegMT->M;
	rotate.identity();
	rightLegMT->M = rotate.makeRotateX(angle) * rightLegMT->M;
	rightLegMT->M = tmp.makeTranslate(0.0, -torsoRadius, 0.0) * rightLegMT->M;

	//left arm
	tmp.identity();
	leftArmMT->M = tmp.makeTranslate(0.0, -cubeSize*1.5 / 2.0, 0.0) * leftArmMT->M;
	rotate.identity();
	leftArmMT->M = rotate.makeRotateX(angle) * leftArmMT->M;
	leftArmMT->M = tmp.makeTranslate(0.0, cubeSize*1.5 / 2.0, 0.0) * leftArmMT->M;

	//right arm
	tmp.identity();
	rightArmMT->M = tmp.makeTranslate(0.0, -cubeSize*1.5 / 2.0, 0.0) * rightArmMT->M;
	rotate.identity();
	rightArmMT->M = rotate.makeRotateX(-angle) * rightArmMT->M;
	rightArmMT->M = tmp.makeTranslate(0.0, cubeSize*1.5 / 2.0, 0.0) * rightArmMT->M;

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
