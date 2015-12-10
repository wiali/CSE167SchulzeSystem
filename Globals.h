#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "House.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Sphere.h"
#include "OBJObject.h"
#include "Rasterizer.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "Skybox.h"
#include "SolarSystem.h"

class Globals
{
    
public:
    
    static Camera camera;
    static Cube cube;
    static Light* light;
    static DrawData drawData;
    static UpdateData updateData;
	static Rasterizer rasterizer;
    //Feel free to add more member variables as needed
	static Sphere sphere;
	//HW2
	static House house;
	static OBJObject* bunny;
	static OBJObject* dragon;
	static OBJObject* bear;

	
	static Drawable* drawable;

	static Skybox skybox;
	//static BezierCurve bezierCurve;
	static float fov;
	
	
	static DirectionalLight dirLight;
	static SpotLight spotLight;
	static PointLight pointLight;
	
	static bool lightControl;

	static bool myEngine;
	static int part;
	static bool debugMode;

	static int lightNum;

	static bool culling;
	static bool showBoundingSpheres;
	static bool showHaloEffect;
	static bool showOrbit;
	static bool motion;
	static bool showDispMap;
	static bool showBumpMap;
	static bool showNormalMap;

	static bool followMars;
	static bool followEarth;
	static bool followVenus;
	static bool followMerc;

	static Group* root;
	static SolarSystem* system;

	Matrix4 id;

};

#endif
