#ifndef CSE167_Texture_h
#define CSE167_Texture_h

#include <iostream>
#include <string>

class Texture
{
    
protected:
    
    const char* filename;
    
    
    
public:
    
    unsigned int id;
	const char* name;
    
    static Texture* emptyTexture;
    
    Texture(void);
    Texture(const char* filename);
	Texture(const char * fname, int i);
    virtual ~Texture(void);
    
	static unsigned char* loadPPM(const char*, int&, int&);

    void bind(void);
    void unbind(void);
    
};

#endif
