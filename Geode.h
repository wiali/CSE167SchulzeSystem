#pragma once
#include "Node.h"

class Geode : public Node {
public:
	void draw(Matrix4 C);
	void update();
	/*Implemented by subclasses*/
	virtual void render();
	
};