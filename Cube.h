#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Drawable.h"
#include "Geode.h"

//class Cube : public Drawable
class Cube : public Geode
{

public:

	float size;

	Cube(float);
	~Cube(void);

	/*virtual void draw(DrawData&);
	void rasterDraw();
	virtual void update(UpdateData&);

	void spin(float);*/
	void render();
	void update(Matrix4);

};

#endif

