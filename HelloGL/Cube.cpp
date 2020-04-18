#include "Cube.h"
#include <iostream>
#include <fstream>


Vertex* Cube::indexedVertices = nullptr;
Color* Cube::indexedColors = nullptr;
GLushort* Cube::indices = nullptr;

int Cube::numVertices = 0;
int Cube::numColors = 0;
int Cube::numIndices = 0;

Cube::Cube(float x, float y, float z)
{
	mPosition = new Vector3{ x, y, z };
}

Cube::~Cube()
{
}

bool Cube::Load(char* path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Can't open text file: " << path << std::endl;
		return false;
	}

	inFile >> numVertices;
	indexedVertices = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		inFile >> indexedVertices[i].x;
		inFile >> indexedVertices[i].y;
		inFile >> indexedVertices[i].z;
	}

	inFile >> numColors;
	indexedColors = new Color[numColors];
	for (int i = 0; i < numColors; i++)
	{
		inFile >> indexedColors[i].r;
		inFile >> indexedColors[i].g;
		inFile >> indexedColors[i].b;
	}

	inFile >> numIndices;
	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++)
	{
		inFile >> indices[i];
	}

	//Debug:
	std::cout << numVertices << std::endl;
	for (int i = 0; i < numVertices; i++)
	{
		std::cout << indexedVertices[i].x << " " << indexedVertices[i].y << " " << indexedVertices[i].z << std::endl;
	}

	std::cout << numColors << std::endl;
	for (int i = 0; i < numColors; i++)
	{
		std::cout << indexedColors[i].r << " " << indexedColors[i].g << " " << indexedColors[i].b << std::endl;
	}

	std::cout << numIndices << std::endl;
	for (int i = 0; i < numIndices; i++)
	{
		std::cout << indices[i] << std::endl;
	}
	//!Debug

	inFile.close();

	return false;
}

void Cube::Draw()
{
	if (indexedVertices != nullptr && numVertices != 0 &&
		indexedColors != nullptr && numColors != 0 &&
		indices != nullptr && numIndices != 0)
	{
		
		glPushMatrix();
		glTranslatef(mPosition->x, mPosition->y, mPosition->z);
		//glRotatef(mRotation, 1.0f, 0.0f, 1.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, indexedColors);

		glPushMatrix();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}
}

void Cube::Update()
{
}

