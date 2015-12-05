#ifdef _WIN32
#include <windows.h>
#endif

#include "Robot.h"
#include "Globals.h"


Robot::Robot(Matrix4 C) : Group() {
	//initialize robot at position specified by C
	init(C);
	//radius
	radius = torsoRadius + 2 * cubeSize;
	//set center
	center = Vector3(C.get(3, 0), C.get(3, 1), C.get(3, 2));
	//center.print("center vector");
}
void Robot::init(Matrix4 C)
{
	//root Group
	root = new Group();

	//geodes
	headRadius = 1.0;
	sphereGeode = new Sphere(headRadius, 10, 10);
	Sphere* torsoGeode = new Sphere(torsoRadius, 10.0, 10.0);

	cubeGeode = new Cube(cubeSize);
	/*Cube* leftLegGeode = new Cube(cubeSize);
	Cube* rightLegGeode = new Cube(cubeSize);
	Cube* leftArmGeode = new Cube(cubeSize);
	Cube* rightArmGeode = new Cube(cubeSize);*/
	//transformations
	Matrix4 temp;

	//torso
	temp = C;
	torsoMT = new MatrixTransform(temp);
	//add child of root
	root->addChild(torsoMT);

	//head
	temp = C;
	temp.makeTranslate(0.0, torsoRadius + headRadius, 0.0);
	headMT = new MatrixTransform(temp);
	torsoMT->addChild(headMT);

	//left leg
	temp = C;
	temp.makeTranslate(-torsoRadius / 3.0, -torsoRadius - cubeSize / 2.0, 0.0);
	leftLegMT = new MatrixTransform(temp);

	//right leg
	temp = C;
	temp.makeTranslate(torsoRadius / 3.0, -torsoRadius - cubeSize / 2.0, 0.0);
	rightLegMT = new MatrixTransform(temp);

	//left arm
	temp = C;
	temp.makeTranslate(-torsoRadius - cubeSize/2.0, 0.0, 0.0);
	leftArmMT = new MatrixTransform(temp);
	
	//right arm
	temp = C;
	temp.makeTranslate(torsoRadius + cubeSize/2.0, 0.0, 0.0);
	rightArmMT = new MatrixTransform(temp);

	//add limbs as children to torso
	torsoMT->addChild(leftLegMT);
	torsoMT->addChild(rightLegMT);
	torsoMT->addChild(leftArmMT);
	torsoMT->addChild(rightArmMT);

	//add cube geode as child of all limbs
	torsoMT->addChild(torsoGeode);

	//add sphere geode as child of head 
	headMT->addChild(sphereGeode);
	leftLegMT->addChild(cubeGeode);
	//leftLegMT->addChild(leftLegGeode);
	rightLegMT->addChild(cubeGeode);
	leftArmMT->addChild(cubeGeode);
	rightArmMT->addChild(cubeGeode);

	//get bounding box
	//center and radius in init

}

Robot::~Robot() 
{
	delete root;
}

void Robot::draw(Matrix4 C)
{

	if (Globals::culling)
	{
		/*int ret = Globals::camera.sphereInFrustum(this->center, this->radius);

		if (ret == Globals::camera.INSIDE || ret == Globals::camera.INTERSECT) {
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
		}*/
	}
	else 
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

}
//update angle
//find pivot point
//translate from pivot point to origin
//rotate at origin
//translate back to pivot point
void Robot::update()
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
	center = Vector3(torsoMT->M.get(3, 0), torsoMT->M.get(3, 1), torsoMT->M.get(3,2));

}

void Robot::animation1() 
{

	Matrix4 trans;
	trans.identity();
	//turn
	if (counter == 210) {
		counter = 0;
		torsoMT->M = torsoMT->M * trans.makeRotateY(90*M_PI/180.0);
		trans.identity();
	}
	//move
	torsoMT->M = torsoMT->M * trans.makeTranslate(0.0,0.0,-.2);
	counter += 1;
}

void Robot::animation2()
{
	Matrix4 trans;
	trans.identity();
	//turn
	if (counter == 210) {
		counter = 0;
		torsoMT->M = torsoMT->M * trans.makeRotateY(-90 * M_PI / 180.0);
		trans.identity();
	}
	//move
	torsoMT->M = torsoMT->M * trans.makeTranslate(0.0, 0.0, -.2);
	counter += 1;
}
