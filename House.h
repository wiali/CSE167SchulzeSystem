#ifndef CSE167_House_h
#define CSE167_House_h

#include "Drawable.h"
#include "Vector4.h"

class House : public Drawable
{

public:

	float size;

	
	Vector4 v1, v2, v3;

	//int nVerts;
	//int indices[];
	//float vertices[];
	//float colors[];

	House();

	House(float);
	virtual ~House(void);

	virtual void draw(DrawData&);
	void rasterDraw();
	virtual void update(UpdateData&);

	//void spin(float);

};

#endif