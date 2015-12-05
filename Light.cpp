#include "Light.h"
#include "Window.h"
#include <iostream>
#include "Globals.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Light::Light()
{
    ambientColor = Color::ambientDefault();
    diffuseColor = Color::diffuseDefault();
    specularColor = Color::specularDefault();
	diffuseColor = Color(1.0, 1.0, 1.0);
    constantAttenuation = 1.0;
    linearAttenuation = 0.0;
    quadraticAttenuation = 0.05;
}

Light::~Light()
{
    //Delete any dynamically allocated memory/objects here
}

void Light::bind(int id)
{
    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }
	//printf("bind id %d\n", id);
    
    //Set the bindID
    bindID = id;
    
    //Configure the light at the bindID
    glEnable(GL_LIGHT0 + bindID);
    
    //Configure the color of the light
    glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, ambientColor.ptr());
    glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, diffuseColor.ptr());
    glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, specularColor.ptr());
    
    //Configure the attenuation properties of the light
    //Add support for Constant Attenuation
    //Add support for Linear Attenuation
	//if (bindID == 1 && Globals::lightNum == 1) { quadraticAttenuation = 0.01; }
    glLightf(GL_LIGHT0 + bindID, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
	glLightf(GL_LIGHT0 + bindID, GL_CONSTANT_ATTENUATION, constantAttenuation);
	glLightf(GL_LIGHT0 + bindID, GL_LINEAR_ATTENUATION, linearAttenuation);
    
    //Position the light
    glLightfv(GL_LIGHT0 + bindID, GL_POSITION, position.ptr());

	//setup pointlight direction
	if (bindID == 1) {
		direction.set(-1 * position[0], -1 * position[1], -1 * position[2], position[3]);
		glLightfv(GL_LIGHT0 + bindID, GL_SPOT_DIRECTION, direction.ptr());
	}
    
    //Setup spotlight direction, angle, and exponent here
	//glLightfv(GL_LIGHT0 + bindID, GL_SPOT_DIRECTION, position.ptr());
	if (bindID == 2) {
		glLightf(GL_LIGHT0 + bindID, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT0 + bindID, GL_SPOT_EXPONENT, exponent);
		direction.set(-1 * position[0], -1 * position[1], -1 * position[2], position[3]);
		glLightfv(GL_LIGHT0 + bindID, GL_SPOT_DIRECTION, direction.ptr());

	}
}

void Light::unbind(void)
{
    glDisable(GL_LIGHT0 + bindID);
    bindID = -1;
}