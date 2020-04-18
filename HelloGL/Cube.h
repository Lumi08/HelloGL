#pragma once
#include <Windows.h> //Required for OpenGL on windows
#include <gl/GL.h> // OpenGl
#include <gl/GLU.h> // OpenGl
#include "GL/freeglut.h" // freeglut library

#include "Structures.h"

class Cube
{
public:
	Cube(Mesh* mesh, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();

private:
	Mesh* mMesh;

	Vector3* mPosition;
};

