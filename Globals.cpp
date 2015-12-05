#include "Globals.h"

Skybox Globals::skybox = Skybox(600.0); 
float Globals::fov = 60.0;
//BezierCurve Globals::bezierCurve;

Camera Globals::camera;

House Globals::house;

Cube Globals::cube(10.0);

//
Sphere Globals::sphere(10.0, 100, 100);
//OBJObject* Globals::bunny = new OBJObject("bunny.obj");
//OBJObject* Globals::dragon = new OBJObject("dragon.obj");
//OBJObject* Globals::bear = new OBJObject("bear.obj");

Light* Globals::light;

PointLight Globals::pointLight;
SpotLight Globals::spotLight;
DirectionalLight Globals::dirLight;

bool Globals::lightControl = false;

int Globals::lightNum = 0;

Drawable* Globals::drawable;

DrawData Globals::drawData;
UpdateData Globals::updateData;
//project 3
Rasterizer Globals::rasterizer;

int Globals::part = 1; //start at part 1
bool Globals::myEngine = false; //use my rasterization
bool Globals::debugMode = false; //bounding box

bool Globals::culling = false;
bool Globals::showBoundingSpheres = false;

Group* Globals::root = new Group();
SolarSystem* Globals::system;
//= new SolarSystem();