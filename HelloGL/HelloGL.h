#pragma once
#include <Windows.h> //Required for OpenGL on windows
#include <gl/GL.h> // OpenGl
#include <gl/GLU.h> // OpenGl
#include "GL/freeglut.h" // freeglut library

#include <vector>
#include <string>
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "SceneObject.h"
#include "Model.h"
#include "MeshLoader.h"

#define REFRESHRATE		16
#define MAXMODELSCOUNT	200

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
	void KeyboardUp(unsigned char key, int k, int y);
	void Mouse(int button, int state, int x, int y);

private: 
	Camera* mCamera;
	SceneObject* mModels[MAXMODELSCOUNT];
	float mRotationValue;
	float mRotationValueX;
	float mRotationValueY;
	float mRotationValueZ;

	Button* mChangeTextureButton;
	Button* mReloadTexturesButton;
	Button* mLoadObjButton;
	Button* mMainMenuButton;
	Button* mMultipleObjectsButton;
	Vector3 mRotation;

	//Lighting
	Vector4* mLightPosition;
	Light* mLightData;
	
	Texture2D* mTextures;
	std::vector<std::string> mTextureNames;
	Mesh** mMeshes;
	Mesh* mCubeMesh;

	int mCurrentTextureIndex,
		mTextureCount,
		mMeshesCount,
		mMultipleModels;

	int mouseStartX;
	bool mInMenu,
		mLoadingObj, 
		mConsoleOutForObj,
		mObjLoaded = true;

	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitLighting();
	void InitTextures();

	void DrawString(const char* text, int x, int y, Color color, bool large);
	bool MouseInsideButton(Button* b, int mouseX, int mouseY);
};

