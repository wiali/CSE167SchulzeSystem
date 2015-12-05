#pragma once
#include "Matrix4.h"
#include "Drawable.h"
#include "Vector4.h"
#include "Camera.h"


class Rasterizer {

public:


	Matrix4 P;
	Matrix4 D;

	int width;
	int height;

	float alpha, beta, gamma;
	float R, G, B;

	Drawable *toDraw;
	/*methods only need to be called when we reshape 
	the window in Window::reshapeCallback */
	Rasterizer(void);
	~Rasterizer();
	
	void clearBuffer();

	void drawPoint(int x, int y, float r, float g, float b);

	void makeProspectiveProjectionMatrix(float fov, float aspect, float nr, float fr);
	void makeViewportMatrix(float x, float y);
	//reshape() replaces resizePixelBuffer();
	Vector4 rasterizeVertex(Vector4& v);
	void rasterize();
	void reshape(int new_width, int new_height);
	void display();
	void rasterizeTriangle(Vector4, Vector4, Vector4);
	bool computeBarycentric(Vector3 a, Vector3 b, Vector3 c, Vector3& p);
	void draw();
};