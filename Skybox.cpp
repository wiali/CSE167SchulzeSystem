#include "Skybox.h"
Skybox::Skybox(float size) 
{
	this->size = size;

}
Skybox::~Skybox()
{
}

void Skybox::draw(Matrix4 C)
{
	float halfSize = size / 2;

	glDisable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(C.ptr());

	//set vertices to white
	glColor3f(1, 1, 1);

	//draw all vertices in counterclockwise order

	//front
	front->bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, -halfSize); //10
	glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, -halfSize); //11
	glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, -halfSize); //01
	glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, -halfSize); //00
	glEnd();
	front->unbind();
	
	// left
	right->bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, -halfSize);
	glEnd();
	right->unbind();
	
	
	//back
	back->bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, halfSize);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, halfSize);
	glEnd();
	back->unbind();
	
	//right
	left->bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, halfSize);
	glEnd();
	left->unbind();
	
	//top
	top->bind();
	glBegin(GL_QUADS); 
	glTexCoord2f(0, 1); glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, halfSize, -halfSize);
	glEnd();
	top->unbind();

	//base image was inverted so swapped 0s and 1s in texCoordf calls
	// base
	base->bind();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, halfSize);
	glEnd();
	base->unbind();

	glPopMatrix();
	glEnable(GL_LIGHTING);
}
void Skybox::update() {}

void Skybox::drawBezierCurve(BezierCurve bc)
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glPointSize(10.0f);

	glBegin(GL_POINTS);
	for (float t = 0.0; t < 1.0; t += 0.01) {
		glColor3f(1.0, 0.0, 0.0);
		glVertex3fv(bc.getPoint(t).ptr());
	}
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);
}
/*
tangents calculated
https://piazza.com/class/iey9l011ui55cs?cid=373
*/
void Skybox::getBZPoints(BezierCurve bc1, BezierCurve bc2, BezierCurve bc3, BezierCurve bc4)
{
	Vector3 point1;
	Vector3 point2;
	Vector3 point3;
	Vector3 point4;
	BezierCurve b;
	BezierCurve b2;
	
	BezierCurve q;
	BezierCurve r;

	Vector3 u0;
	Vector3 u1;
	Vector3 tanU;
	Vector3 tanV;
	Vector3 v0;
	Vector3 normal;

	//get bezier patch points
	int tCtr = 0;
	float t2 = 0.01;
	for (float t = 0.0; t < 1.0; t += 0.01, t2+=0.01) {
		b = BezierCurve(bc1.getPoint(t), bc2.getPoint(t),
			bc3.getPoint(t), bc4.getPoint(t));
		
		//first sliver
		q = BezierCurve(bc1.getPoint(t), bc2.getPoint(t),
			bc3.getPoint(t), bc4.getPoint(t));
		r = BezierCurve(bc1.getPoint(t + (float)0.00001), bc2.getPoint(t + (float)0.00001),
			bc3.getPoint(t + (float)0.00001), bc4.getPoint(t + (float)0.00001));
		
		int zCtr = 0;
		for (float z = 0.0;  z < 1.0; z += 0.01) {
			b2 = BezierCurve(b.cp1, b.cp2, b.cp3, b.cp4);
			Vector3 bcPt = b2.getPoint(z);		
			bezierPoints[tCtr][zCtr] = bcPt; //store point in array

			u0 = q.getPoint(z);
			u1 = q.getPoint(z + (float)0.00001);
			//first tangent
			tanU = u1 - u0;

			v0 = r.getPoint(z + (float)0.00001);
			//second tangent
			tanV = v0 - u0;

			//normalize tan vectors
			tanU = tanU.normalize();
			tanV = tanV.normalize();

			//calc normal
			normal = tanU.cross(tanV);
			//normal = tanV.cross(tanU);
			normal = normal + Vector3(1, 1, 1);
			normal = normal.scale(.5);
			normal.normalize();
			normals[tCtr][zCtr] = normal;    //store normal

			zCtr += 1;			
		}
		tCtr += 1;
	}
}

void Skybox::drawFlag()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	
	logo->bind();
	
	Vector3 bezierPt1;
	Vector3 bezierPt2;
	Vector3 bezierPt3;
	Vector3 bezierPt4;

	
	Shader* shade = new Shader("Sample.vert", "sample.frag");
	shade->bind();

	//glBegin(GL_POINTS); //points works
	//loop thru array and draw quads
	glBegin(GL_QUADS);
	for (int i = 0.0; i < 99/*99*/; i++) {
		for (int j = 0.0; j < 99/*99*/; j++) {
			
			//set normal
			Vector3 norm = normals[i][100 - j];
			glNormal3f(norm[0], norm[1], norm[2]);
			glColor3f(1.0, 1.0, 1.0);


			bezierPt2 = bezierPoints[i][j]; //0,0
			glTexCoord2f(i / 100.0, float(100 - j + 1) / 100.0); //0,1
			glVertex3fv(bezierPt2.ptr());

			bezierPt3 = bezierPoints[i][j + 1]; //0,1
			glTexCoord2f(i / 100.0, float(100 - j) / 100.0); //0,0
			glVertex3fv(bezierPt3.ptr());
			
			bezierPt4 = bezierPoints[i + 1][j + 1]; //1,1
			glTexCoord2f(float(i + 1) / 100.0, float(100 - j) / 100.0); //1,0
			glVertex3fv(bezierPt4.ptr());

			bezierPt1 = bezierPoints[i+1][j]; //1,0
			glTexCoord2f(float(i + 1) / 100.0, float(100 - j+1) / 100.0); //1,1
			glVertex3fv(bezierPt1.ptr());

		}
	}
	glEnd();	
	
	shade->unbind();
	logo->unbind();
	glPopMatrix();

	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);

}
