#include <iostream>

#include "glee.h"
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Sphere.h"
#include "OBJObject.h"
#include "Matrix4.h"
#include "Globals.h"
#include "Rasterizer.h"
#include "BezierCurve.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

int Window::spinDirection = 1;
int Window::switchBall = 1;
int Window::select = 0;

int Window::renderMode = 0;

bool Window::shiftPressed = false;

Vector3 lastpoint, currentpoint;
int movement;

Vector3 controlP1 = { 0.0, 0.0, 0.0 };
Vector3 controlP2 = { 5.0, 3.0, 3.0 };
Vector3 controlP3 = { 10.0, -3.0, -3.0 };
Vector3 controlP4 = { 15.0, 0.0, 0.0 };

Vector3 controlP5 = { 0.0, 4.0, 0.0 };
Vector3 controlP6 = { 5.0, 7.0, 0.0 };
Vector3 controlP7 = { 10.0, 1.0, 0.0 };
Vector3 controlP8 = { 15.0, 4.0, 0.0 };

Vector3 controlP9 = { 0.0, 8.0, 0.0 };
Vector3 controlP10 = { 5.0, 11.0, 3.0 };
Vector3 controlP11 = { 10.0, 5.0, -3.0 };
Vector3 controlP12 = { 15.0, 8.0, 0.0 };

Vector3 controlP13 = { 0.0, 12.0, 0.0 };
Vector3 controlP14 = { 5.0, 15.0, 3.0 };
Vector3 controlP15 = { 10.0, 9.0, -3.0 };
Vector3 controlP16 = { 15.0, 12.0, 0.0 };

void Window::initialize(void)
{

	Globals::light = &Globals::dirLight;
    
    //Initialize cube matrix:
    //Globals::cube.toWorld.identity();

	//Init house matrix
	Globals::house.toWorld.identity();
    
    //Setup the cube's material properties
    Color color(0x23ff27ff);
	//Globals::cube.material.color = color;

	//init skybox textures
	/*Globals::skybox.front = new Texture("Skybox_Water222_front.ppm");
	Globals::skybox.back = new Texture("Skybox_Water222_back.ppm");
	Globals::skybox.base = new Texture("Skybox_Water222_base.ppm");
	Globals::skybox.top = new Texture("Skybox_Water222_top.ppm");
	Globals::skybox.left = new Texture("Skybox_Water222_left.ppm");
	Globals::skybox.right = new Texture("Skybox_Water222_right.ppm");*/

	Globals::skybox.front = new Texture("front_neb.ppm");
	Globals::skybox.back = new Texture("back_neb.ppm");
	Globals::skybox.base = new Texture("down_neb.ppm");
	Globals::skybox.top = new Texture("up_neb.ppm");
	Globals::skybox.left = new Texture("left_neb.ppm");
	Globals::skybox.right = new Texture("right_neb.ppm");

	//init logo texture
	Globals::skybox.logo = new Texture("Ucsd-logo.ppm");

	//horizontal curves
	BezierCurve bc1 = BezierCurve(controlP1, controlP2, controlP3, controlP4);
	BezierCurve bc2 = BezierCurve(controlP5, controlP6, controlP7, controlP8);
	BezierCurve bc3 = BezierCurve(controlP9, controlP10, controlP11, controlP12);
	BezierCurve bc4 = BezierCurve(controlP13, controlP14, controlP15, controlP16);

	//get bezier curve points and place in array
	Globals::skybox.getBZPoints(bc1, bc2, bc3, bc4);

	Matrix4 id;
	id.identity();

	Globals::system = new SolarSystem(id);

	//Globals::bunny->scale(14.72 * tan(0.523599));

	//Globals::dragon->scale(18.44* tan(0.523599));

	//Globals::bear->scale(2.0 * tan(0.523599));
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
//Print frames per second
int frame = 0, time, timebase = 0;
void Window::idleCallback()
{
	/*frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		printf("FPS:%4.2f \n",
			frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}*/
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //Rotate cube; if it spins too fast try smaller values and vice versa
    //Globals::cube.spin(0.0005*spinDirection);
    
    //Call the update function on cube
    //Globals::cube.update(Globals::updateData);

	//Bounce ball

	//Call the update function on ball
	//Globals::sphere.update(Globals::updateData);

	//Call the update function on bunny
	//Globals::bunny->update(Globals::updateData);

	//Call the update function on dragon
	//Globals::dragon->update(Globals::updateData);

	//Call the update function on bear
	//Globals::bear->update(Globals::updateData);

	//Globals::light->update(Globals::updateData);

    
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(Globals::fov, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum

	//Change perspective projection matrix
	//Change viewport matrix
	//Call resize pixel buffer
	Globals::rasterizer.reshape(w, h);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	//Globals::drawable = &Globals::skybox;
    //Clear color and depth buffers
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearStencil(0x4);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    //Globals::light.bind(0);

	Globals::pointLight.bind(1);
	
	//Globals::dirLight.bind(0);
	//Globals::light->bind(0);
	//Globals::spotLight.bind(2);
	
	//if dl on then bind to 0

	//Globals::directionalLight->bind(0);
	//Set lighting on for animals 
	//glEnable(GL_LIGHTING);

	Matrix4 identity;
	identity.identity();
	Globals::skybox.draw(identity);

	//glEnable(GL_LIGHTING);
	Globals::system->draw(identity);
	Globals::system->update();
	//glDisable(GL_LIGHTING);
	//Globals::skybox.drawFlag();
	if (Globals::light)
	{
		//Globals::light->draw(Globals::drawData);
	}

	if (select == 1) {	
		//Draw the cube!
		//Globals::cube.draw(Globals::drawData);
		//Globals::sphere.draw(Globals::drawData);
	} else if (select == 2) {
		//glDisable(GL_LIGHTING);
		//Draw bunny
		//Globals::bunny->draw(Globals::drawData);
		//glEnable(GL_LIGHTING);
	} else if (select == 3) {
		//Draw dragon
		//Globals::dragon->draw(Globals::drawData);
	}
	else if (select == 4) {
		//Draw bear
		//Globals::bear->draw(Globals::drawData);
	}
	else {

	}
    
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}


//TODO: Keyboard callbacks!
void Window::keyboardCallback(unsigned char key, int x, int y) {

	switch (key) {
	case '0':
	{
		//toggle light control
		Globals::lightControl = !Globals::lightControl;
		printf("Toggled light control\n");
	}	break;
	case '1':
	{
		//control directional light
		//rotations change the direction of the light
		//
		Globals::pointLight.unbind();
		Globals::spotLight.unbind();

		Globals::light = &Globals::dirLight;
		Globals::dirLight.bind(0);
		Globals::lightNum = 0;
	}	break;
	case '2':
	{
		printf("2 pressed");
		//control point light
		//Globals::light->unbind();
		
		Globals::dirLight.unbind();
		Globals::spotLight.unbind();
		Globals::pointLight.unbind();
		Globals::pointLight.bind(1);
		//Globals::spotLight.bind(1);

		Globals::light = &Globals::pointLight;
		Globals::lightNum = 1;
		
	}	break;
	case '3':
	{
		printf("3 pressed");
		//control spot light
		//Globals::light->unbind();
		Globals::spotLight.unbind();
		Globals::dirLight.unbind();
		Globals::pointLight.unbind();
		Globals::spotLight.bind(2);
		Globals::lightNum = 2;

		Globals::light = &Globals::spotLight;

	}	break;
	case 'c':
	{
		Globals::showBoundingSpheres = !Globals::showBoundingSpheres;
		printf("toggled collision detection, show bounding spheres val %d \n", Globals::showBoundingSpheres);
	}
	default:
		break;
	}
	
	if (select == 1) {
		moveCube(key);
	} 
	else if (select == 2) {
		//Globals::bunny->handleKeys(key);
	}
	else if (select == 3) {
		//Globals::dragon->handleKeys(key);
	}
	else if (select == 4) {
		//Globals::bear->handleKeys(key);	
	}
	
}

//TODO: Function Key callbacks!
void Window::specialFuncCallback(int key, int x, int y)
{
	if (key == GLUT_KEY_F1) {
		/* Switch to sphere*/
		printf("F1 pressed\n");
		select = 1;
		Globals::camera.reset();
		//Globals::drawable = &Globals::sphere;
		
	} else if (key == GLUT_KEY_F2) {
		/* Switch to bunny*/
		printf("F2 pressed\n");
		select = 2;
		Globals::camera.reset();
		Globals::drawable = &Globals::skybox;
		//Globals::drawable = Globals::bunny;

	} else if (key == GLUT_KEY_F3) {
		/* Switch to dragon*/
		printf("F3 pressed\n");
		select = 3;
		Globals::camera.reset();
		//Globals::drawable = Globals::dragon;
	}
	else if (key == GLUT_KEY_F4) {
		//bear
		printf("F4 pressed\n");
		select = 4;
		Globals::camera.reset();
		//Globals::drawable = Globals::bear;
	}
	

}

//TODO: Mouse callbacks!
void Window::mouseCallback(int button, int state, int x, int y) 
{
	 {
		int mod = glutGetModifiers();

		if (mod != 0) //SHIFT=1 
		{
			switch (mod)
			{
			case 1:
				if (state == GLUT_DOWN) {
					if (button == GLUT_LEFT_BUTTON) {
						Globals::fov += 5;
						reshapeCallback(width, height);
						if (Globals::lightControl)
						{
							Matrix4 trans;
							trans.makeScale(1.01);
							Globals::light->position = trans * Globals::light->position;
							Globals::light->toWorld = trans * Globals::light->toWorld;
							if (Globals::lightNum == 1) {
								Globals::light->bind(1);
							}
							else if (Globals::lightNum == 2) {
								Globals::light->bind(2);
							}
						}
						else 
						{
							Matrix4 trans;
							trans.makeScale(1.1);
							//Globals::drawable->toWorld = trans * Globals::drawable->toWorld;
						}

					}
					else if (button == GLUT_RIGHT_BUTTON)
					{
						Globals::fov -= 5;
						reshapeCallback(width, height);
						if(Globals::lightControl)
						{
							Matrix4 trans;
							trans.makeScale(.99);
							Globals::light->position = trans * Globals::light->position;
							Globals::light->toWorld = trans * Globals::light->toWorld;
							if (Globals::lightNum == 1) {
								Globals::light->bind(1);
							}
							else if (Globals::lightNum == 2){
								Globals::light->bind(2);
							}
						}
						else 
						{
							Matrix4 trans;
							trans.makeScale(.9);
							//Globals::drawable->toWorld = trans * Globals::drawable->toWorld;
						}
					}
					mod = 0;
					break;
				}
			}
		}
		else {
			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				if (state == GLUT_DOWN) {
					movement = GLUT_LEFT_BUTTON;
					lastpoint = trackBallMapping(x, y);
				}
				break;
			case GLUT_RIGHT_BUTTON:
				if (state == GLUT_DOWN) {
					movement = GLUT_RIGHT_BUTTON;
					lastpoint = Vector3(x, y, 0);
				}
				break;
				//case middle:
			default:
				break;
			}
		}
		//lastpoint = currentpoint;
		//lastpoint = trackBallMapping(x, y);
	}


}

//TODO: Mouse Motion callbacks!
void Window::motionCallback(int x, int y) 
{
	Vector3 direction;
	float velocity;
	float rot_angle;
	Matrix4 temp;

	currentpoint = trackBallMapping(x, y);
	direction = (currentpoint - lastpoint);

	//if (Globals::lightControl) {}
	//else {
		switch (movement) {
		case GLUT_LEFT_BUTTON:
				velocity = direction.magnitude();
				if (velocity > 0.001) 
				{
					Vector3 rotationAxisA;
					rotationAxisA = lastpoint.cross(currentpoint);

					rot_angle = currentpoint.angle(lastpoint);

					rotationAxisA = rotationAxisA.normalize();

					temp = temp.makeRotateArbitrary(rotationAxisA, rot_angle);
					if (Globals::lightControl) {
						if (Globals::lightNum == 0) {
							//rotate direction
							Globals::dirLight.position = temp * Globals::dirLight.position;
							Globals::dirLight.bind(0);
						}
						else if (Globals::lightNum == 1) 
						{
							//rotate the light around the origin of the world coordinate system
							//printf("lightNum %d", Globals::lightNum);
							Globals::light->position = temp * Globals::light->position;
							Globals::light->toWorld = temp * Globals::light->toWorld;
							Globals::light->bind(1);
						}
						else if (Globals::lightNum == 2) 
						{
							Globals::light->position = temp * Globals::light->position;
							Globals::light->toWorld = temp * Globals::light->toWorld;
							Globals::light->bind(2);
						}

					}
					else {
						//Globals::drawable->toWorld = temp * Globals::drawable->toWorld;
					}
					lastpoint = currentpoint;
				}
			break;

		case GLUT_RIGHT_BUTTON:
			currentpoint = Vector3(x, y, 0); 
			//rotate camera
			Globals::camera.e = Globals::camera.e +
				Vector3((currentpoint[0]-lastpoint[0])*0.009, (currentpoint[1] - lastpoint[1])*0.009, 0);
			if (Globals::lightControl && Globals::lightNum == 2) {
				//mouse up / down should make the spot wider / narrower, 
				Globals::light->cutoff = Globals::light->cutoff + (currentpoint[1] - lastpoint[1])*0.01;
				//printf("cutoff value %f\n", Globals::light->cutoff);

				//left / right should make the spot edge sharper / blurrier
				Globals::light->exponent = Globals::light->exponent + (currentpoint[0] - lastpoint[0])*0.9;
				if (Globals::light->exponent < 0)
					Globals::light->exponent = 1.0;
				printf("exponent: %f\n", Globals::light->exponent);
				Globals::light->bind(2);
				lastpoint = currentpoint;
			}
			else {
				Matrix4 temp;
				temp = temp.makeTranslate((currentpoint[0] - lastpoint[0])*0.01, (currentpoint[1] - lastpoint[1])*-0.01, 0);
				//Globals::drawable->toWorld = temp * Globals::drawable->toWorld;
				lastpoint = currentpoint;
			}

			//lastpoint = currentpoint;
			Globals::camera.update();
			//reshapeCallback(width, height);
			break;
		}
		


}

Vector3 Window::trackBallMapping(int x, int y)
{
	Vector3 v;    // Vector v is the synthesized 3D position of the mouse location on the trackball
	float d;     // this is the depth of the mouse location: the delta between the plane through the center of the trackball and the z position of the mouse
	v[0] = (float)(2.0*x - width) / width;   // this calculates the mouse X position in trackball coordinates, which range from -1 to +1
	v[1] = (float)(height - 2.0*y) / height;   // this does the equivalent to the above for the mouse Y position
	v[2] = 0.0;   // initially the mouse z position is set to zero, but this will change below
	d = (float)v.magnitude();    // this is the distance from the trackball's origin to the mouse location, without considering depth (=in the plane of the trackball's origin)
	d = (d<1.0) ? d : 1.0;   // this limits d to values of 1.0 or less to avoid square roots of negative values in the following line
	v[2] = (float)sqrtf(1.001 - d*d);  // this calculates the Z coordinate of the mouse position on the trackball, based on Pythagoras: v.z*v.z + d*d = 1*1
	v = v.normalize(); // Still need to normalize, since we only capped d, not v.
	return v;  // return the mouse location on the surface of the trackball
}

void Window::moveCube(unsigned char key) {}

