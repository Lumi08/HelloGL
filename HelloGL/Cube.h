#pragma once
#include <Windows.h> //Required for OpenGL on windows
#include <gl/GL.h> // OpenGl
#include <gl/GLU.h> // OpenGl
#include "GL/freeglut.h" // freeglut library

#include "Structures.h"

class Cube
{
public:
	Cube(float x, float y, float z);
	~Cube();

	void Draw();
	void Update();

	static bool Load(char* path);

private:
	static Vertex* indexedVertices;
	static Color* indexedColors;
	static GLushort* indices;

	static int	numVertices,
				numColors,
				numIndices;


	Vector3* mPosition;

};

