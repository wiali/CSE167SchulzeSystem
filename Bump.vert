#version 130
// This preprocessor call should only fail if your OpenGL version
// is older than 3.0, which was released in August 2008.

void main() {
gl_TexCoord[0] = gl_MultiTexCoord0;

// Set the position of the current vertex
gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}