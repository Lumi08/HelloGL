#pragma once
#include <Windows.h> //Required for OpenGL on windows
#include <gl/GL.h> // OpenGl
#include <gl/GLU.h> // OpenGl
#include "GL/freeglut.h" // freeglut library

#include "GLUTCallbacks.h"

#define REFRESHRATE			16

class HelloGL
{
public:
	// Constructor definition
	HelloGL(int argc, char* argv[]);

	//deconstructor
	~HelloGL(void);

	void Display();
	void Update();

private: 
	float rotation;
};

