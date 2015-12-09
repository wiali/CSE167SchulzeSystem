#pragma once
#include "Node.h"

class Geode : public Node {
public:
	Vector3 wireframeColor = Vector3(0.0, 0.0, 1.0);
	float angle;
	void draw(Matrix4 C);
	void update();
	/*Implemented by subclasses*/
	virtual void render();
	virtual void initShader();
	virtual void renderWire();
	virtual void renderHalo();
	virtual void renderOrbit();
	virtual void renderDisk();
};