#pragma once
#include <Windows.h> //Required for OpenGL on windows
#include <gl/GL.h> // OpenGl
#include <gl/GLU.h> // OpenGl
#include "GL/freeglut.h" // freeglut library

#include "GLUTCallbacks.h"

#define REFRESHRATE		16

struct Vector3
{
	float x, y, z;
};

struct Camera
{
	Vector3 eye, center, up;
};

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
	float mRotation;

	void DrawCube();
};

