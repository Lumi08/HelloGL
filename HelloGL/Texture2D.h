#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

class Texture2D
{
private:
	GLuint mID;
	int mWidth, 
		mHeight;
public:
	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);

	GLuint GetID() const { return mID; }
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
};

