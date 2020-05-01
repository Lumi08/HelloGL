#include "HelloGL.h"
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitObjects();
	InitLighting();
	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGl program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutMouseFunc(GLUTCallbacks::Mouse);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800); //Set the viewport to be the entire window
	gluPerspective(45, 1, 0.1, 100); //Set the correct perspective
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glCullFace(GL_BACK);
	
}

void HelloGL::InitObjects()
{
	mRotationValue = 0.0f;
	mRotationValueX = 0.0f;
	mRotationValueY = 0.0f;
	mRotationValueZ = 0.0f;
	mCurrentTextureIndex = 0;

	mCamera = new Camera();
	mCamera->eye = Vector3{ 0.0f, 0.0f, 10.0f };
	mCamera->center = Vector3{ 0.0f, 0.0f, 0.0f };
	mCamera->up = Vector3{ 0.0f, 1.0f, 0.0f };

	Mesh* cubeMesh = MeshLoader::Load((char*)"Models/cube.txt");
	//Mesh* pyramidMesh = MeshLoader::Load((char*)"Text Files/Pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Textures/unnamed.raw", 512, 512);

	InitTextures();
	InitMeshes();

	mInMenu = true;
	mModel = new Model(cubeMesh, &mTextures[0], 0.0f, 0.0f, 0.0f);
	mChangeTextureButton = new Button(10, 10, 200, 50);
	mMainMenuButton = new Button(300, 500, 200, 50); 
	mReloadTexturesButton = new Button(10, 65, 200, 50);
}

void HelloGL::InitLighting()
{
	mLightPosition = new Vector4{ 0.0, 0.0, 1.0, 0.0 };
	
	mLightData = new Light();
	mLightData->Ambient = Vector4{ 0.2, 0.2, 0.2, 1.0 };
	mLightData->Diffuse = Vector4{ 0.8, 0.8, 0.8, 1.0 };
	mLightData->Specular = Vector4{ 0.2, 0.2, 0.2, 1.0 };
}

void HelloGL::InitTextures()
{
	std::vector<std::string> fileNames;
	std::string directory = "Textures/*.*";
	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	if (!((hFind = FindFirstFile(directory.c_str(), &fileData)) == INVALID_HANDLE_VALUE)) {
		while (FindNextFile(hFind, &fileData)) {
			fileNames.push_back(fileData.cFileName);
			mTextureNames.push_back(fileData.cFileName);
		}
	}
	FindClose(hFind);

	mTextures = new Texture2D[fileNames.size()];
	mTextureCount = fileNames.size();
	std::string fileLocation = "Textures/";
	for (int i = 0; i < fileNames.size(); i++)
	{
		mTextures[i].Load((fileLocation + fileNames[i]).c_str(), 512, 512);
	}
}

void HelloGL::InitMeshes()
{
	std::vector<std::string> fileNames;
	std::string directory = "Models/*.*";
	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	if (!((hFind = FindFirstFile(directory.c_str(), &fileData)) == INVALID_HANDLE_VALUE)) {
		while (FindNextFile(hFind, &fileData)) {
			fileNames.push_back(fileData.cFileName);
		}
	}
	FindClose(hFind);

	mMeshes = new Mesh*[fileNames.size()];
	mMeshesCount = fileNames.size();
	std::string fileLocation = "Models/";
	for (int i = 0; i < fileNames.size(); i++)
	{
		std::cout << fileNames[i] << " Loaded" << std::endl;
		mMeshes[i] = MeshLoader::Load((fileLocation + fileNames[i]).c_str());
	}
}

HelloGL::~HelloGL(void)
{

}

void HelloGL::Display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(mCamera->eye.x, mCamera->eye.y, mCamera->eye.z, mCamera->center.x, mCamera->center.y, mCamera->center.z, mCamera->up.x, mCamera->up.y, mCamera->up.z);

	//Draw 3D

	if (!mInMenu)
	{
		glRotatef(mRotationValueX, 1.0f, 0.0f, 0.0f);
		glRotatef(mRotationValueY, 0.0f, 1.0f, 0.0f);
		mModel->Draw();
	}

	//End 3D Drawing

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 800, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);

	//Draw 2D


	if (mInMenu)
	{
		DrawString("Welcome To My OpenGl Project", 250, 100, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("To Add textures add .raw files to the Textures Folder", 100, 200, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("Controls:", 100, 250, Color{ 1.0f, 0.0f, 0.0f }, true);
		DrawString("W A S D - Control the camera", 100, 300, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("Q - Zooms the camera in", 100, 350, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("E - Zooms the camera out", 100, 400, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("", 100, 450, Color{ 1.0f, 1.0f, 1.0f }, true);


		mMainMenuButton->Draw();
		DrawString("Play", 375, 530, Color{ 0.0f, 0.0f, 0.0f }, true);
	}
	else
	{
		mChangeTextureButton->Draw();
		DrawString("Change Texture", 30, 40, Color{ 0.0f, 0.0f, 0.0f }, true);
		DrawString(("Current Texture: " + mTextureNames.at(mCurrentTextureIndex)).c_str(), 30, 700, Color{ 1.0f, 1.0f, 1.0f }, true);
		mReloadTexturesButton->Draw();
		DrawString("Reload Textures", 30, 95, Color{ 0.0f, 0.0f, 0.0f }, true);
	}

	//End 2D Drawing

	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	//glMatrixMode(GL_PROJECTION); 
	//glLoadIdentity(); 
	//gluLookAt(mCamera->eye.x, mCamera->eye.y, mCamera->eye.z, mCamera->center.x, mCamera->center.y, mCamera->center.z, mCamera->up.x, mCamera->up.y, mCamera->up.z); //where to look in the scene

	//std::cout <<"eye x: " << mCamera->eye.x << " eye Y: " <<  mCamera->eye.y << " eye Y: " << mCamera->eye.z << " center X: " << mCamera->center.x << " center Y: " << mCamera->center.y << " center z: " << mCamera->center.z << " up X: " << mCamera->up.x << " up Y: " << mCamera->up.y << " up Z: " << mCamera->up.z << std::endl;

	//mCamera->eye.x = sin(glutGet(GLUT_ELAPSED_TIME)) * 10;
	//mCamera->eye.z = cos(glutGet(GLUT_ELAPSED_TIME)) * 10;

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(mLightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(mLightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(mLightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(mLightPosition->x));

	mModel->Update();

	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	/*
	mCamera->eye.x += 0.1; Moves the camera to the left
	mCamera->eye.x -= 0.1; Moves the camera to the right

	mCamera->eye.y -= 0.1; Moves the camera up
	mCamera->eye.y += 0.1; Moves the camer down

	mCamera->eye.z -= 0.1; Zooms in
	mCamera->eye.z += 0.1; Zooms out
	*/
	if (key == 'w')
	{
		mRotationValueX -= 1.0;
	}

	if (key == 's')
	{
		mRotationValueX += 1.0;
	}

	if (key == 'a')
	{
		mRotationValueY -= 1.0;
	}

	if (key == 'd')
	{
		mRotationValueY += 1.0;
	}

	if (key == 'q')
	{
		mCamera->eye.z -= 0.1;
	}

	if (key == 'e')
	{
		mCamera->eye.z += 0.1;
	}
}

void HelloGL::KeyboardUp(unsigned char key, int k, int y)
{

}

void HelloGL::Mouse(int button, int state, int x, int y)
{
	if (button == 0)
	{
		if (state == GLUT_DOWN)
		{
			if (MouseInsideButton(mChangeTextureButton, x, y))
			{
				mCurrentTextureIndex++;
				mModel->SetTexture(&mTextures[mCurrentTextureIndex]);

				if (mCurrentTextureIndex >= mTextureCount)
				{
					mCurrentTextureIndex = 0;
				}
			}

			if (MouseInsideButton(mReloadTexturesButton, x, y))
			{
				mModel->SetTexture(&mTextures[0]);
				InitTextures();
				mCurrentTextureIndex = 0;
			}

			if (MouseInsideButton(mMainMenuButton, x, y))
			{
				mInMenu = false;
			}
		}
	}
}

void HelloGL::DrawString(const char* text, int x, int y, Color color, bool large)
{
	glPushMatrix();

	glColor4f(color.r, color.g, color.b, 1.0f);
	glRasterPos2f(x, y);
	if (large)
	{
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	}
	else
	{
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (unsigned char*)text);
	}

	glPopMatrix();
}

bool HelloGL::MouseInsideButton(Button* b, int mouseX, int mouseY)
{
	if (mouseX >= b->x && mouseX < b->x + b->w && mouseY >= b->y && mouseY < b->y + b->h)
	{
		return true;
	}
	return false;
}


