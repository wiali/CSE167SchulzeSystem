#include "Material.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Material::Material()
{
    //Material setup goes hurr
    ambientColor = Color::ambientMaterialDefault();
    diffuseColor = Color::diffuseMaterialDefault();
    specularColor = Color::specularMaterialDefault();
    emissionColor = Color::emissionMaterialDefault();
    shininess = 10.0;
    
    //Set the initial color to a random pastel color
    //Can be removed once materials are implemented
    color = Color::randomPastel();
}

Material::~Material()
{
    //Delete any dynamically allocated memory/objects here
}

void Material::apply(void)
{
    //Set the material properties for ambient, diffuse, specular, emission, and shininess
    //Hint: Lookup how glMaterialfv works
	//const GLfloat ambColor[] = { 0.0215, 0.1745, 0.0215 };
	/*float ambColor[4] = { 0.0215, 0.1745, 0.0215,1.0 };
	float diffColor[4] = { 0.07568, 0.61424,0.07568,1.0 };
	float specColor[4] = { 0.633, 0.727811, 0.633,1.0 };
	shininess = 0.6;*/
	//printf("Window select %d \n", Window::select);
	if (Window::select == 1) {
	//emerald sphere
		float ambColor[4] = { 0.0215, 0.1745, 0.0215,1.0 };
		float diffColor[4] = { 0.07568, 0.61424,0.07568,1.0 };
		float specColor[4] = { 0.633, 0.727811, 0.633,1.0 };
		//shininess = .6;
		GLfloat shiny[] = { 1 };
		//float shiny[4] = { shininess,shininess,shininess,shininess };
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ambColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	}
	else if (Window::select == 2) {
		//shiny gold bunny
		float ambColor[4] = { 0.24725, 0.1995, 0.0745,1.0 };
		float diffColor[4] = { 0.75164, 0.60648, 0.22648, 1.0 };
		float specColor[4] = { 0.628281, 0.555802, 0.366065, 1.0 };
		shininess = 0.0;
		float shiny[4] = { shininess,shininess,shininess,shininess };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ambColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	}
	else if (Window::select == 3) {
		//ruby dragon
		float ambColor[4] = { 0.1745, 0.01175, 0.01175,1.0 };
		float diffColor[4] = { 0.61424, 0.04136, 0.04136, 1.0 };
		float specColor[4] = { 0.727811, 0.626959, 0.626959, 1.0 };
		shininess = 10.0;
		float shiny[4] = { shininess,shininess,shininess,shininess };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ambColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	}
	else if (Window::select == 4) {
		//turquoise bear
		float ambColor[4] = { 0.1, 0.18725, 0.1745,1.0 };
		float diffColor[4] = { 0.396, 0.74151, 0.69102, 1.0 };
		float specColor[4] = { 0.297254, 0.30829, 0.306678, 1.0 };
		shininess = 255.0;
		float shiny[4] = { shininess,shininess,shininess,shininess };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ambColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	}
	//glMaterialfv

    //Set the color property (can be removed once materials are implemented)
    //Used for projects 1, 2, and 3
    //glColor3fv(color.ptr());
}



