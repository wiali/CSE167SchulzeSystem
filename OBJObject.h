#ifndef CSE167_OBJObject_h
#define CSE167_OBJObject_h

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Vector3.h"
#include "Drawable.h"
#include "Vector4.h"

/*struct Face
{
    int vertexIndices[3];
    int normalIndices[3];
	//int colorIndices[3];
    //Add more members as necessary
};*/

class OBJObject : public Drawable
{
    
protected:
	    
	Face face;
	bool hasRGBValues;
    //Storage vectors
    /*std::vector<Vector3*>* vertices;
	std::vector<Vector3*>* colors;
    std::vector<Vector3*>* normals;
    std::vector<Face*>* faces;*/
    
    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    
    //Parse
    void parse(std::string&);
    
	
public:
	Matrix4 modelMatrix;
	double angle;
	bool spin_clockwise = true;
	float minX = 0; float maxX = 0;
	float minY = 0; float maxY = 0;
	float minZ = 1; float maxZ = -1;

	OBJObject(std::string);
    virtual ~OBJObject(void);
    
	
	void center();

	virtual void draw(DrawData&);
	void rasterDraw();
    virtual void update(UpdateData&);

	//Move object
	void changeSpinDirection();
	void moveX(float);
	void moveY(float);
	void moveZ(float);
	void scale(float);
	void orbit(float);
	void reset();

	void handleKeys(unsigned char);
    
};

#endif
