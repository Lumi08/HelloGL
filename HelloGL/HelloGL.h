#pragma once
#include <Windows.h> //Required for OpenGL on windows
#include <gl/GL.h> // OpenGl
#include <gl/GLU.h> // OpenGl
#include "GL/freeglut.h" // freeglut library

#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "MeshLoader.h"

#define REFRESHRATE		16

class HelloGL
{
public:
	// Constructor definition
	HelloGL(int argc, char* argv[]);

	//deconstructor
	~HelloGL(void);

	void Display();
	void Update();

	void Keyboard(unsigned char key, int x, int y);

private: 
	Camera* mCamera;
	Cube* mCube[100];
	float mRotation;

	void InitObjects();
	void InitGL(int argc, char* argv[]);
};

