#include "Vector3.h"
#include <math.h>
#include <iostream>
#include <cstring>
#include "Vector4.h"

Vector3::Vector3()
{
    std::memset(m, 0, sizeof(m));
}

Vector3::Vector3(float m0, float m1, float m2)
{
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
}

Vector3::~Vector3()
{
    //
}

float* Vector3::ptr()
{
    return &m[0];
}

void Vector3::set(float x, float y, float z)
{
    m[0] = x;
    m[1] = y;
    m[2] = z;
}

void Vector3::set(int index, float value)
{
    m[index] = value;
}

float& Vector3::operator [] (int loc)
{
    return m[loc];
}


/*Vector3& Vector3::operator = (Vector3& a) {
	Vector3 b;
	m[0] = a[0];
	m[1] = a[1];
	m[2] = a[2];
	printf("=B: %f, %f, %f", a[0], a[1], a[2]);
	return *this;

};*/
Vector3 Vector3::add(Vector3 a)
{
    Vector3 b;
    
    //
	b[0] = a[0] + this->m[0];
	b[1] = a[1] + this->m[1];
	b[2] = a[2] + this->m[2];

    return b;
}

Vector3 Vector3::operator + (Vector3 a)
{
    return add(a);
}

Vector3 Vector3::subtract(Vector3 a)
{
    Vector3 b;
    
    //
	b[0] = this->m[0] - a[0];
	b[1] = this->m[1] - a[1];
	b[2] = this->m[2] - a[2];

    return b;
}

Vector3 Vector3::operator - (Vector3 a)
{
    return subtract(a);
}

Vector3 Vector3::negate(void)
{
    Vector3 b;
    
    //
	b[0] = this->m[0] * -1;
	b[1] = this->m[1] * -1;
	b[2] = this->m[2] * -1;
    
    return b;
}

Vector3 Vector3::scale(float s)
{
    Vector3 b;
    
    //
	b[0] = this->m[0] * s;
	b[1] = this->m[1] * s;
	b[2] = this->m[2] * s;
    
    return b;
}

Vector3 Vector3::multiply(float a)
{
    Vector3 b;
    
    //
	b[0] = this->m[0] * a;
	b[1] = this->m[1] * a;
	b[2] = this->m[2] * a;
    
    return b;
}

Vector3 Vector3::operator * (float a)
{
    return multiply(a);
}

Vector3 Vector3::multiply(Vector3 a)
{
    Vector3 b;
    
    //Component-wise multiplication
	b[0] = this->m[0] * a[0];
	b[1] = this->m[1] * a[1];
	b[2] = this->m[2] * a[2];
    
    return b;
}

Vector3 Vector3::operator * (Vector3 a)
{
    return multiply(a);
}


float Vector3::dot(Vector3 a)
{
	float dot = 0.0;
	//
	dot = this->m[0] * a[0]
		+ this->m[1] * a[1]
		+ this->m[2] * a[2];
    
    return dot;
}

Vector3 Vector3::cross(Vector3 a)
{
    Vector3 b;
    
    //Formula: <a2b3 - a3b2, a3b1-a1b3,a1b2-a2b1>
	//         <t1a2 - t2a1, t2a0 - t0a2, t0a1 - t1a0>
	//this = a, b = a
	b[0] = (this->m[1] * a[2]) - (this->m[2] * a[1]);
	b[1] = (this->m[2] * a[0]) - (this->m[0] * a[2]);
	b[2] = (this->m[0] * a[1]) - (this->m[1] * a[0]);
    return b;
}

float Vector3::angle(Vector3 a)
{
	if (this->magnitude() == 0 || a.magnitude() == 0) {
		return 0;
	}
    //Formula
	return acos( this->dot(a) / (this->magnitude() * a.magnitude()) );
    
}

float Vector3::magnitude(void)
{
    //Formula
	//printf("%f::", (this->m[0])*(this->m[0]) + (this->m[1])*(this->m[1]) + (this->m[2])*(this->m[2]));
    return sqrt( (this->m[0])*(this->m[0]) + (this->m[1])*(this->m[1]) + (this->m[2])*(this->m[2])   );
}

Vector3 Vector3::normalize(void)
{
    Vector3 b;
    /*Avoid divide by zero*/
	if (this->magnitude() == 0) {
		b[0] = 0;
		b[1] = 0;
		b[2] = 0;
	} else {
		b[0] = this->m[0] / this->magnitude();
		b[1] = this->m[1] / this->magnitude();
		b[2] = this->m[2] / this->magnitude();
	}
    //
	//printf("this magnitude %f \n", this->magnitude());
	
    return b;
}

Vector4 Vector3::toVector4(float w)
{
    Vector4 b(m[0], m[1], m[2], w);
    return b;
}

void Vector3::print(std::string comment)
{
    std::cout << comment << std::endl;
    std::cout << "<x:" << m[0] <<  ", y:" << m[1] << ", z:" << m[2] << ">" << std::endl;
}
