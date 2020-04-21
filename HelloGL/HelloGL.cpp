#include "HelloGL.h"
#include <string>
#include <iostream>

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
	glutMouseFunc(GLUTCallbacks::Mouse);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800); //Set the viewport to be the entire window
	gluPerspective(45, 1, 0.1, 1000); //Set the correct perspective
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
	mRotation = 0.0f;

	mCamera = new Camera();
	mCamera->eye = Vector3{ 0.0f, 0.0f, 10.0f };
	mCamera->center = Vector3{ 0.0f, 0.0f, 0.0f };
	mCamera->up = Vector3{ 0.0f, 1.0f, 0.0f };

	Mesh* cubeMesh = MeshLoader::Load((char*)"Text Files/Cube.txt");
	//Mesh* pyramidMesh = MeshLoader::Load((char*)"Text Files/Pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Textures/unnamed.raw", 512, 512);

	/*for (int i = 0; i < 100; i++)
	{
		mObjects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000 / 10.0f));
	}*/

	cube = new Cube(cubeMesh, nullptr, 0.0f, 0.0f, 0.0f);
	mButton = new Button(10, 10, 300, 50);

}

void HelloGL::InitLighting()
{
	mLightPosition = new Vector4{ 0.0, 0.0, 1.0, 0.0 };
	
	mLightData = new Light();
	mLightData->Ambient = Vector4{ 0.2, 0.2, 0.2, 1.0 };
	mLightData->Diffuse = Vector4{ 0.8, 0.8, 0.8, 1.0 };
	mLightData->Specular = Vector4{ 0.2, 0.2, 0.2, 1.0 };
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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Draw 3D

	cube->Draw();

	//End 3D Drawing

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 800, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);

	//Draw 2D

	mButton->Draw();

	glRasterPos2f(200, 200);
	
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"Testing");

	//End 2D Drawing

	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity(); // loads identity matrix
	gluLookAt(mCamera->eye.x, mCamera->eye.y, mCamera->eye.z,
		mCamera->center.x, mCamera->center.y, mCamera->center.z,
		mCamera->up.x, mCamera->up.y, mCamera->up.z); //where to look in the scene

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(mLightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(mLightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(mLightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(mLightPosition->x));

	cube->Update();

	//Sleep(10);
	mRotation += 0.5;

	if (mRotation > 360.0f)
	{
		mRotation = 0.0f;
	}

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
	if (key == 'e')
	{
		mCamera->eye.x += 0.1;
	}

	if (key == 'a')
	{
		cube->SetTexture((char*)"Textures/Penguins.raw", 512, 512);
	}

	if (key == 'd')
	{
		cube->SetTexture((char*)"Textures/unnamed.raw", 512, 512);
	}

	if (key == 'q')
	{
		cube->ClearTexture();
	}
}

void HelloGL::Mouse(int button, int state, int x, int y)
{
	if (button == 3)
	{
		//mCamera->eye.z += 0.1;
		cube->SetZ(cube->GetZ() - 0.1);
	}

	if (button == 4)
	{
		cube->SetZ(cube->GetZ() + 0.1);
	}

	if (button == 0)
	{
		if (state == GLUT_DOWN)
		{
			if (MouseInsideButton(mButton, x, y))
			{
				cube->SetTexture((char*)"Textures/Penguins.raw", 512, 512);
			}
		}

		if (state == GLUT_UP)
		{
			if (mouseStartX > x)
			{
				std::cout << "Moved left" << std::endl;
				mouseStartX = 0;
			}
		}
	}
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();

	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (unsigned char*)text);

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


