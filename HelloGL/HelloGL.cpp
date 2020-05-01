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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGl program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
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
	
	mCubeMesh = MeshLoader::Load((char*)"Models/cube.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Textures/unnamed.raw", 512, 512);

	InitTextures();

	mInMenu = true;
	mLoadingObj = false;
	mObjLoaded = false;
	mMultipleModels = false;
	mRotating = false;

	mModels[0] = new Model(mCubeMesh, nullptr, 0.0f, 0.0f, 0.0f);
	mChangeTextureButton = new Button(10, 10, 200, 50);
	mMainMenuButton = new Button(300, 600, 200, 50); 
	mReloadTexturesButton = new Button(10, 65, 200, 50);
	mLoadObjButton = new Button(590, 10, 200, 50);
	mMultipleObjectsButton = new Button(10, 120, 200, 50);
	mRotateObjectsButton = new Button(10, 175, 200, 50);
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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(mCamera->eye.x, mCamera->eye.y, mCamera->eye.z, mCamera->center.x, mCamera->center.y, mCamera->center.z, mCamera->up.x, mCamera->up.y, mCamera->up.z);

	//Draw 3D

	if (!mInMenu)
	{
		if (mMultipleModels)
		{
			for (int i = 0; i < MAXMODELSCOUNT; i++)
			{
				if (mModels[i] != nullptr)
				{
					mModels[i]->Draw();
				}
			}
		}
		else
		{
			glRotatef(mRotationValueX, 1.0f, 0.0f, 0.0f);
			glRotatef(mRotationValueY, 0.0f, 1.0f, 0.0f);
			glRotatef(mRotationValueZ, 0.0f, 0.0f, 1.0f);
			glRotatef(mRotationValue, 1.0f, 1.0f, 0.0f);
			mModels[0]->Draw();
		}
	}

	//End 3D Drawing

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);

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
		DrawString("Due to Obj Reader Limitations", 100, 200, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("Texturing is not allowed while a obj is loaded", 100, 230, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("Lighting is also Disabled while a obj is loaded", 100, 260, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("All obj files are found in Models/", 100, 290, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("Controls:", 100, 400, Color{ 1.0f, 0.0f, 0.0f }, true);
		DrawString("W A S D Z X - Control the camera", 100, 450, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("Q - Zooms the camera in", 100, 500, Color{ 1.0f, 1.0f, 1.0f }, true);
		DrawString("E - Zooms the camera out", 100, 550, Color{ 1.0f, 1.0f, 1.0f }, true);

		mMainMenuButton->Draw();
		DrawString("Play", 375, 630, Color{ 0.0f, 0.0f, 0.0f }, true);
	}
	else
	{
		if (!mObjLoaded)
		{
			mChangeTextureButton->Draw();
			DrawString("Change Texture", 30, 40, Color{ 0.0f, 0.0f, 0.0f }, true);
			DrawString(("Current Texture: " + mTextureNames.at(mCurrentTextureIndex)).c_str(), 30, 700, Color{ 1.0f, 1.0f, 1.0f }, true);
			mReloadTexturesButton->Draw();
			DrawString("Reload Textures", 30, 95, Color{ 0.0f, 0.0f, 0.0f }, true);

			mMultipleObjectsButton->Draw();
			if (!mMultipleModels)
			{
				DrawString("Multiple Objects", 30, 150, Color{ 0.0f, 0.0f, 0.0f }, true);
			}
			else
			{
				DrawString("Single Object", 30, 150, Color{ 0.0f, 0.0f, 0.0f }, true);
			}
		}
		
		mLoadObjButton->Draw();
		if (mObjLoaded)
		{
			DrawString("Return To Cube", 605, 45, Color{ 0.0f, 0.0f, 0.0f }, true);
		}
		else
		{
			DrawString("Load Simple Obj", 605, 45, Color{ 0.0f, 0.0f, 0.0f }, true);
		}

		if (!mMultipleModels)
		{
			mRotateObjectsButton->Draw();
			if (!mRotating)
			{
				DrawString("Rotate Object", 30, 205, Color{ 0.0f, 0.0f, 0.0f }, true);
			}
			else
			{
				DrawString("Stop Rotating", 30, 205, Color{ 0.0f, 0.0f, 0.0f }, true);
			}
		}
		

		if (mLoadingObj)
		{
			DrawString("OPEN CONSOLE", 602, 95, Color{ 1.0f, 0.0f, 0.0f }, true);
			mConsoleOutForObj = true;
		}
	}

	//End 2D Drawing

	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	if (mConsoleOutForObj)
	{

		std::string path;
		std::cout << "Enter File Path: ";
		std::cin >> path;
		std::cout << path << std::endl;
		mLoadingObj = false;
		mConsoleOutForObj = false;

		Mesh* tempMesh = new Mesh();
		tempMesh = MeshLoader::LoadSimpleObj(path.c_str());

		if (tempMesh != nullptr)
		{
			if (mMultipleModels)
			{
				for (int i = 0; i < MAXMODELSCOUNT; i++)
				{
					mModels[i]->SetTexture(nullptr);
					mModels[i]->SetMesh(tempMesh);
				}
			}
			else
			{
				mModels[0]->SetTexture(nullptr);
				mModels[0]->SetMesh(tempMesh);
			}
			mObjLoaded = true;
			//mModel = new Model(tempMesh, nullptr, 0.0f, 0.0f, 0.0f);
		}
		else
		{
			std::cout << "Can not load OBJ: " << path << std::endl;
		}
	}

	if (mRotating)
	{
		mRotationValue++;
	}
	if (mRotationValue >= 360)
	{
		mRotationValue = 0;
	}


	glLightfv(GL_LIGHT0, GL_AMBIENT, &(mLightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(mLightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(mLightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(mLightPosition->x));

	mModels[0]->Update();

	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		if (mMultipleModels)
		{
			mCamera->eye.y -= 0.1;
		}
		else
		{
			mRotationValueX -= 1.0;
		}
	}

	if (key == 's')
	{
		if (mMultipleModels)
		{
			mCamera->eye.y += 0.1;
		}
		else
		{
			mRotationValueX += 1.0;
		}
	}

	if (key == 'a')
	{
		if (mMultipleModels)
		{
			mCamera->eye.x += 0.1;
		}
		else
		{
			mRotationValueY -= 1.0;
		}
	}

	if (key == 'd')
	{
		if (mMultipleModels)
		{
			mCamera->eye.x -= 0.1;
		}
		else
		{
			mRotationValueY += 1.0;
		}
	}
	if (key == 'x')
	{
		if (mMultipleModels)
		{

		}
		else
		{
			mRotationValueZ -= 1.0;
		}
	}
	if (key == 'z')
	{
		if (mMultipleModels)
		{

		}
		else
		{
			mRotationValueZ += 1.0;
		}
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

				if (mMultipleModels)
				{
					for (int i = 0; i < MAXMODELSCOUNT; i++)
					{
						mModels[i]->SetTexture(&mTextures[mCurrentTextureIndex]);
					}
				}
				else
				{
					mModels[0]->SetTexture(&mTextures[mCurrentTextureIndex]);
				}

				if (mCurrentTextureIndex >= mTextureCount)
				{
					mCurrentTextureIndex = 0;
				}
			}

			if (MouseInsideButton(mReloadTexturesButton, x, y))
			{
				mModels[0]->SetTexture(&mTextures[0]);
				InitTextures();
				mCurrentTextureIndex = 0;
			}

			if (MouseInsideButton(mLoadObjButton, x, y))
			{
				if (mObjLoaded)
				{
					if (mMultipleModels)
					{
						mObjLoaded = false;

						for (int i = 0; i < MAXMODELSCOUNT; i++)
						{
							mModels[i]->SetMesh(mCubeMesh);
						}
					}
					else
					{
						mModels[0]->SetMesh(mCubeMesh);
					}
					mObjLoaded = false;
				}
				else
				{
					mLoadingObj = true;
				}
			}

			if (MouseInsideButton(mMainMenuButton, x, y))
			{
				mInMenu = false;
			}
			
			if (MouseInsideButton(mMultipleObjectsButton, x, y))
			{
				mMultipleModels = !mMultipleModels;


				if (mMultipleModels)
				{
					mObjLoaded = false;

					for (int i = 0; i < MAXMODELSCOUNT; i++)
					{
						mModels[i] = new Model(mCubeMesh, &mTextures[mCurrentTextureIndex], (((rand() % 400) / 10.0f) - 20.0f), ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
					}
				}
				else
				{
					mModels[0] = new Model(mCubeMesh, &mTextures[mCurrentTextureIndex], 0.0f, 0.0f, 0.0f);
				}
			}

			if (MouseInsideButton(mRotateObjectsButton, x, y))
			{
				mRotating = !mRotating;
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


