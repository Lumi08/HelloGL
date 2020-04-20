#pragma once
#include <Windows.h> //Required for OpenGL on windows
#include <gl/GL.h> // OpenGl
#include <gl/GLU.h> // OpenGl
#include "GL/freeglut.h" // freeglut library

#include "GLUTCallbacks.h"
#include "Structures.h"
#include "SceneObject.h"
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
	void Mouse(int button, int state, int x, int y);


private: 
	Camera* mCamera;
	SceneObject* mObjects[200];
	float mRotation;

	SceneObject* cube;
	Button* mButton;

	//Lighting
	Vector4* mLightPosition;
	Light* mLightData;

	int mouseStartX;

	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitLighting();

	void DrawString(const char* text, Vector3* position, Color* color);
	bool MouseInsideButton(Button* b, int mouseX, int mouseY);
};

