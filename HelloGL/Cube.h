#pragma once
#include <Windows.h> //Required for OpenGL on windows
#include <gl/GL.h> // OpenGl
#include <gl/GLU.h> // OpenGl
#include "GL/freeglut.h" // freeglut library

#include "SceneObject.h"
#include "Structures.h"
#include "Texture2D.h"

class Cube : public SceneObject
{
public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();

private:
	Material* mMaterial;
	float mRotation;
};
