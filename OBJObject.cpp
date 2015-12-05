#include "OBJObject.h"
#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Globals.h"
#include "math.h"
#include <sstream>
#include <fstream>

#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)

OBJObject::OBJObject(std::string filename) : Drawable()
{
    this->vertices = new std::vector<Vector3>();
    this->normals = new std::vector<Vector3>();
    this->faces = new std::vector<Face>();
	this->colors = new std::vector<Vector3>();
    
    parse(filename);

	toWorld.identity();
	spin_clockwise = true;
	angle = 0.0;

	this->center();
	
}

OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    
	delete vertices; //deleteVector(Vector3*, vertices);
	delete normals; //deleteVector(Vector3*, normals);

	delete colors; //deleteVector(Vector3*, colors);
	delete faces; //   deleteVector(Face*, faces);

}

void OBJObject::center() {
	//Compute "bounding box"
	//calculate bounding box of the object, by going through X, Y, and Z, and getting the minimum and maximum values
	for (int i = 0; i < (int)faces->size(); i++) {
		face = faces->at(i);

		for (int j = 0; j < 3; j++) {
			//Get vertex
			Vector3 vertVector = vertices->at(face.vertexIndices[j] - 1);
			//glVertex3f(vertVector[0], vertVector[1], vertVector[2]);
			minX = min(minX, vertVector[0]);
			maxX = max(maxX, vertVector[0]);

			minY = min(minY, vertVector[1]);
			maxY = max(maxY, vertVector[1]);

			minZ = min(minZ, vertVector[2]);
			maxZ = max(maxZ, vertVector[2]);
		}

	}

	printf("MinX: %f \n MaxX: %f \n MinY: %f \n MaxY: %f \n MinZ: %f \n MaxZ: %f \n", minX, maxX, minY, maxY, minZ, maxZ);

	/*
	Step2: Get the center = (max+min)/2 xfor X, Y, and Z. */
	float centerX = (maxX + minX) / 2.0;
	float centerY = (maxY + minY) / 2.0;
	float centerZ = (maxZ + minZ) / 2.0;

	Vector3 center(centerX, centerY, centerZ);

	center.print("Center vector");

	/*Get halfSize = (max - min)/2 for X,Y,Z.  
	float midX = (maxX - minX) / 2.0;
	float midY = (maxY - minY) / 2.0;
	float midZ = (maxZ - minZ) / 2.0;*/

	Matrix4 trans;
	trans.makeTranslate(-centerX,-centerY,-centerZ);
	toWorld = trans * toWorld;
	
	/*
Make scaleVector = Vector3 filled with (1 / largest value in halfSize)
	Step3: Apply Translation(-center), then apply Scale(scaleVector)*/
}
void OBJObject::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_TRIANGLES);
    
    
    //Loop through the faces
    //For each face:
    //  Look up the vertices, normals (if they exist), and texcoords (if they exist)
    //  Draw them as triplets:
    
    //      glNorm(normals->at(face.normalIndices[0]))
    //      glVert(vertices->at(face.vertexIndices[0]))
    //      Etc.
    //
	//Loop thru faces vector
	for (int i = 0; i < (int)faces->size(); i++) {
		face = faces->at(i);

		for (int j = 0; j < 3; j++) {
			Vector3 normVector = normals->at(face.normalIndices[j] - 1);
			normVector = normVector.normalize(); //
			glNormal3f(normVector[0], normVector[1], normVector[2]);


			if (hasRGBValues) {
				Vector3 colorVector = colors->at(face.vertexIndices[j] - 1);
				glColor3f(colorVector[0], colorVector[1], colorVector[2]);
			}
			else { glColor3f(1, 1, 1); 
			}
			//Draw vertex last
			Vector3 vertVector = vertices->at(face.vertexIndices[j] - 1);
			glVertex3f(vertVector[0], vertVector[1], vertVector[2]);
			
		}

	}
    
    glEnd();
    
    glPopMatrix();
}

void OBJObject::rasterDraw() {

	Globals::rasterizer.clearBuffer();
	Vector4 v1, v2, v3;
	Vector3 vert;
	Vector3 norm;
	//stop flashing triangles
	srand(1);

	for (int i = 0; i < (int)faces->size(); i++) {
		Face face = faces->at(i);

		//Get vertices
		vert = vertices->at(face.vertexIndices[0] - 1);
		v1.set(vert[0], vert[1], vert[2], 1.0);

		vert = vertices->at(face.vertexIndices[1] - 1);
		v2.set(vert[0], vert[1], vert[2], 1.0);

		vert = vertices->at(face.vertexIndices[2] - 1);
		v3.set(vert[0], vert[1], vert[2], 1.0);

		//Get normals
		norm = normals->at(face.normalIndices[0] - 1);
		n1.set((float)norm[0], (float)norm[1], (float)norm[2]);
		n1 = n1.normalize();

		norm = normals->at(face.normalIndices[1] - 1);
		n2.set((float)norm[0], (float)norm[1], (float)norm[2]);
		n2 = n2.normalize();

		norm = normals->at(face.normalIndices[2] - 1);
		n3.set((float)norm[0], (float)norm[1], (float)norm[2]);
		n3 = n3.normalize();


		if (Globals::part == 1) {
			Globals::rasterizer.rasterizeVertex(v1);
			Globals::rasterizer.rasterizeVertex(v2);
			Globals::rasterizer.rasterizeVertex(v3);
		}
		else {
			//pass vertices into rasterizeTriangle
			Globals::rasterizer.rasterizeTriangle(v1, v2, v3);
		}
	}

	Globals::rasterizer.display();
}

void OBJObject::update(UpdateData& data)
{
    //
}

void OBJObject::parse(std::string& filename)
{    
	std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens;
	std::vector<std::string> faceToken1, faceToken2, faceToken3;
    std::string token;
	float x, y, z;  // vertex coordinates
	float r, g, b;  // vertex color
    int lineNum = 0;
	Vector3 normalized;
    
    std::cout << "Starting parse..." << std::endl;	
    
    //While all your lines are belong to us
    while (std::getline(infile, line))
    {
		
        //Progress
        if(++lineNum % 100000 == 0) {
            std::cout << "At line " << lineNum << std::endl;
			printf(line.c_str());
			printf("\n");

		}
        //Split a line into tokens by delimiting it on spaces
        //"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
        tokens.clear();
        tokens = split(line, ' ', tokens);

		//Skip empty lines
		if (tokens.empty()) {
			printf("Line %s", line.c_str());
			continue;			
		}
        
        //If first token is a v then it gots to be a vertex
        if(tokens.at(0).compare("v") == 0)
        {
            //Parse the vertex line
			hasRGBValues = false;
			//Vertices(x,y,z)
            x = std::stof(tokens.at(1));
            y = std::stof(tokens.at(2));
            z = std::stof(tokens.at(3));
            vertices->push_back(Vector3(x, y, z));

			if (tokens.size() == 7 ) {
				hasRGBValues = false;
				//Colors(r,g,b)
				r = std::stof(tokens.at(4));
				g = std::stof(tokens.at(5));
				b = std::stof(tokens.at(6));
				colors->push_back(Vector3(r, g, b));
			}
			
        }
        else if(tokens.at(0).compare("vn") == 0)
        {
            //Parse the normal line
			x = std::stof(tokens.at(1));
			y = std::stof(tokens.at(2));
			z = std::stof(tokens.at(3));
			
			Vector3 normalized = Vector3(x,y,z);
			normalized = normalized.normalize();
			normals->push_back(Vector3(normalized[0], normalized[1], normalized[2]));
        }
        else if(tokens.at(0).compare("f") == 0)
        {
			Face face;//= new Face;

			//Parse the face line
			faceToken1.clear();
			faceToken2.clear();
			faceToken3.clear();

			faceToken1 = OBJObject::split(tokens.at(1), '/');
			faceToken2 = OBJObject::split(tokens.at(2), '/');
			faceToken3 = OBJObject::split(tokens.at(3), '/');

			face.vertexIndices[0] = std::stof(faceToken1.at(0));
			face.normalIndices[0] = std::stof(faceToken1.at(2));
			
			face.vertexIndices[1] = std::stof(faceToken2.at(0));
			face.normalIndices[1] = std::stof(faceToken2.at(2));

			face.vertexIndices[2] = std::stof(faceToken3.at(0));
			face.normalIndices[2] = std::stof(faceToken3.at(2));

			if (lineNum == 100000) {
				printf("vi0: %d ni0: %d vi1: %d ni1: %d vi2: %d vi2: %d \n", face.vertexIndices[0], face.normalIndices[0],
					face.vertexIndices[1], face.normalIndices[1], face.vertexIndices[2], face.normalIndices[2]);
			}

            faces->push_back(face);
        }
        else if(tokens.at(0).compare("How does I are C++?!?!!") == 0)
        {
            //Parse as appropriate
            //There are more line types than just the above listed
            //See the Wavefront Object format specification for details
        }
		else if (tokens.at(0).compare("#") == 0) 
		{
			//Do nothing
		} //Blank line
        
    }
    
    std::cout << "Done parsing." << std::endl;
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void OBJObject::changeSpinDirection() {
	spin_clockwise = !spin_clockwise;	
}

void OBJObject::moveX(float val) {
	Matrix4 trans;
	trans.makeTranslate(val, 0, 0);
	toWorld = trans * toWorld;
}
void OBJObject::moveY(float val) {
	Matrix4 trans;
	trans.makeTranslate(0, val, 0);
	toWorld = trans * toWorld;
}
void OBJObject::moveZ(float val) {
	Matrix4 trans;
	trans.makeTranslate(0, 0, val);
	toWorld = trans * toWorld;
}
void OBJObject::scale(float val) {
	Matrix4 trans;
	trans.makeScale(val);
	toWorld = trans * toWorld;
}
void OBJObject::orbit(float val) {
	Matrix4 trans;
	trans.makeRotateZ(val);
	toWorld = toWorld * trans;
}

void OBJObject::reset() {
	Matrix4 trans;
	trans.identity();
	toWorld = trans;
}

void OBJObject::handleKeys(unsigned char key) {

	switch (key) {
	case 'c': {
		changeSpinDirection();
		break;
	}
	case 'x': {
		moveX(-0.1);
		break;
	}
	case 'X': {
		moveX(0.1);
		break;
	}
	case 'y': {
		moveY(-0.1);
		break;
	}
	case 'Y': {
		moveY(0.1);
		break;
	}	
	case 'z': {
		moveZ(-0.1);
		break;
	}
	case 'Z': {
		moveZ(0.1);
		break;
	}
	case 'r': {
		reset();
		break;
	}
	case 'o': {
		orbit(-0.18);
		break;
	}
	case 'O': {
		orbit(0.18);
		break;
	}
	case 's': {
		scale(.9);
		break;
	}
	case 'S': {
		scale(1.1);
		break;
	}
	default: 
		break;
	}
}
