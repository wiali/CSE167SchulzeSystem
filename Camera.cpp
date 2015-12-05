#include "Camera.h"

Camera::Camera()
{
    c.identity();
    e.set(0.0, 0.0, 30.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);

	c.print("\nC matrix");
	ci.print("\nCi matrix");
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix()
{
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    return ci;
}

void Camera::update()
{
    //Update the Camera Matrix using d, e, and up
    //Solve for the z, x, and y axes of the camera matrix
	/**
	* Formula taken from discussion 2 slides
	* C^-1 = R^-1 * T^-1
	*/

	printf("camera update Camera e ");
	e.print("");
	d.print("\ncamera update Camera d ");
	up.print("\ncamera update Camera up ");
	
	Vector3 z = e - d;
	z.print("camera update z");
	z = z.normalize();
	z.print("\ncamera update normalized z");
	
	Vector3 x = up.cross(z);
	x.print("\ncam update x");
	x = x.normalize();
	x.print("\ncamera update normalized x");
	
	Vector3 y = z.cross(x);
	y.print("\ncam update y");
    //Use these axes and the e vector to create a camera matrix c
	/*c.set(x[0], x[1], x[2], 0,
		y[0], y[1], y[2], 0,
		z[0], z[1], z[2], 0,
		e[0], e[1], e[2], 1);*/

	//Use c to solve for an inverse camera matrix ci
	/**
	* Formula taken from discussion 2 slides
	* C^-1 = R^-1 * T^-1
	* ci = (T * R)^-1 = R^T * T^-1
	*/
	c.print("\nCamera matrix");
	Matrix4 temp;
	//temp = temp.transpose();
	temp.set(x[0], y[0], z[0], 0,
		x[1], y[1], z[1], 0,
		x[2], y[2], z[2], 0,
		0, 0, 0, 1);
	//temp = temp.transpose();
	temp.print("\nR transposed matrix");
	Matrix4 inverse;
	/*inverse.set(
		1, 0, 0, -e[0],
		0, 1, 0, -e[1],
		0, 0, 1, -e[2],
		0, 0, 0, 1);*/
	inverse.set(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				-e[0], -e[1], -e[2], 1);
	inverse.print("\nT inverse matrix");
	ci = temp* inverse;
	/*ci.set(x[0], x[1], x[2], -e[0],
		   y[0], y[1], y[2], -e[1],
		   z[0], z[1], z[2], -e[2],
		  0, 0, 0, 1);*/

	ci.print("\nCi Matrix");

	//Matrix4 product = c * ci;
	//product.print("Product of cam matrix and inverse cam matrix");

}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}

void Camera::reset() 
{
	c.identity();
	e.set(0.0, 0.0, 20.0);
	d.set(0.0, 0.0, 0.0);
	up.set(0.0, 1.0, 0.0);

	c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
	ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);

}
