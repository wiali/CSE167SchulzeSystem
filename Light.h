#ifndef CSE167_Light_h
#define CSE167_Light_h

#include "Matrix4.h"
#include "Vector4.h"
#include "Color.h"
#include "Drawable.h"
#include <vector>

class Light : public Drawable
{
    
protected:
    
    int bindID = -1;
    
public:
    
    Vector4 position;
	Vector4 direction;
	float cutoff, exponent;
    
	Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    
public:
    
    Light();
    virtual ~Light(void);
    
    void bind(int);
    void unbind(void);

	//void draw(Matrix4);
    
};

#endif
