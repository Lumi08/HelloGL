#include "Texture2D.h"

#include <fstream>
#include <iostream>

using namespace std;

Texture2D::Texture2D()
{
	
}


Texture2D::~Texture2D()
{
	glDeleteTextures(1, &mID);
}

bool Texture2D::Load(const char* path, int width, int height)
{

	char* tempTextureData;
	int fileSize;
	ifstream inFile;

	mWidth = width;
	mHeight = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file: " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end);
	fileSize = (int)inFile.tellg();
	tempTextureData = new char[fileSize];
	inFile.seekg(0, ios::beg);
	inFile.read(tempTextureData, fileSize);
	inFile.close();

	cout << "Texture " << path << " Successfully loaded" << endl;

	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete [] tempTextureData;
	return true;
}
