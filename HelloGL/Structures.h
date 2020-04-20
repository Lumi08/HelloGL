#pragma once
#include <Windows.h> //Required for OpenGL on windows
#include <gl/GL.h> // OpenGl
#include <gl/GLU.h> // OpenGl
#include "GL/freeglut.h" // freeglut library

struct Vector3
{
	float x, y, z;
};

struct Vector4
{
	float x, y, z, w;
};

struct Camera
{
	Vector3 eye, 
			center, 
			up;
};

struct Color
{
	GLfloat r, 
			g, 
			b;
};

struct Vertex
{
	GLfloat x, 
			y, 
			z;
};

struct TexCoord
{
	GLfloat u,
			v;
};

struct Light
{
	Vector4 Ambient,
			Diffuse,
			Specular;
};

struct Material
{
	Vector4 Ambient,
			Diffuse,
			Specular;
	GLfloat Shininess;
};

struct Mesh
{
	Vertex* Vertices;
	Vector3* Normals;
	GLushort* Indices;
	TexCoord* TexCoords;
	int VertexCount,
		NormalCount,
		IndexCount,
		TexCoordCount;
};

struct Button
{
	int x, y, w, h;

	Button(int xPos, int yPos, int width, int height)
	{
		x = xPos;
		y = yPos;
		w = width;
		h = height;
	}

	void Draw()
	{
		glColor3f(0.6f, 0.6f, 0.6f);

		/*
		 *	draw background for the button.
		 */
		glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x, y + h);
		glVertex2i(x + w, y + h);
		glVertex2i(x + w, y);
		glEnd();

		glLineWidth(0.1);
	}
};
