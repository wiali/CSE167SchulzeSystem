#ifndef CSE167_Drawable_h
#define CSE167_Drawable_h

#include "Shader.h"
#include <iostream>
#include "Matrix4.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Material.h"
#include "Vector3.h"
#include <float.h>
#include <math.h>
#include <vector>

struct Face
{
	int vertexIndices[3];
	int normalIndices[3];
	//int colorIndices[3];
	//Add more members as necessary
};

class Drawable
{

    
public:
	Face face;
	bool hasRGBValues;

	std::vector<Vector3>* vertices;
	std::vector<Vector3>* colors;
	std::vector<Vector3>* normals;
	std::vector<Face>* faces;

	//normals for HW3 part4
	Vector3 n1, n2, n3;
    
    Matrix4 toWorld;
    Material material;
    
    Drawable(void);
    ~Drawable(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
};

#endif
