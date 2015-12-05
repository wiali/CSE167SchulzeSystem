#ifndef CSE167_Window_h
#define CSE167_Window_h

#include "Shader.h"
#include "Vector3.h"
#include "BezierPatch.h"
#include "Matrix4.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
	static int spinDirection;
	static int switchBall;
	static int select;
	static int renderMode;

	static bool shiftPressed;

    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	//
	static void keyboardCallback(unsigned char, int, int);
	static void specialFuncCallback(int, int, int);

	static Vector3 trackBallMapping(int, int);

	static void mouseCallback(int, int, int, int);
	static void motionCallback(int, int);

	static void moveCube(unsigned char);
    
};

#endif

