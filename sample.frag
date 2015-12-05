// shadertype=glsl
#version 130
// Once again, this preprocessor will only fail if your OpenGL version
// is horribly outdated.


// The fragment shader will get the values of these varying qualifiers
// from the vertex shader
varying vec4 position;
varying vec3 normal;
uniform sampler2D textureSampler;

// Another sample fragment shader is provided in the Spring 2015 midterm 2.
void main(){
   // Variables used for calculations declared here
   vec3 finalColor = vec3(0.0, 0.0, 0.9);
   vec4 fColor = vec4(0);
   
   //Find out texture coordinate
   vec2 st = gl_TexCoord[0].st;
   
   //Find out texture color at that coordinate
   vec4 textureColor = texture2D(textureSampler, st);
   
   //Set fragment color to the color we want
   //gl_FragColor = manipulate(textureColor);
   fColor = textureColor.rgba;
   if (fColor.b <=  0.1 && fColor.g <=  0.1 && fColor.r <=  0.1) 
     fColor = vec4(0,0,0,0);
   else
     fColor = vec4(normal.bgr,textureColor.a);
	 //fColor = normal.bgra;

   gl_FragColor = fColor;
}