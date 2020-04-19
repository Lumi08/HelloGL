#include "HelloGL.h"
#include <iostream>

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitObjects();
	glutMainLoop();
}

void HelloGL::InitObjects()
{
	mRotation = 0.0f;

	mCamera = new Camera();
	mCamera->eye = Vector3{ 0.0f, 0.0f, 5.0f };
	mCamera->center = Vector3{ 0.0f, 0.0f, 0.0f };
	mCamera->up = Vector3{ 0.0f, 1.0f, 0.0f };


	Mesh* cubeMesh = MeshLoader::Load((char*)"Text Files/Cube.txt");
	//Mesh* pyramidMesh = MeshLoader::Load((char*)"Text Files/Pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Textures/unnamed.raw", 512, 512);

	cube = new Cube(cubeMesh, texture, 0.0f, 0.0f, 0.0f);
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
	glCullFace(GL_BACK);
	
}

HelloGL::~HelloGL(void)
{

}

void HelloGL::Display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glRotatef(mRotation, 1.0f, 1.0f, 1.0f);

	cube->Draw();

	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity(); // loads identity matrix
	gluLookAt(mCamera->eye.x, mCamera->eye.y, mCamera->eye.z,
		mCamera->center.x, mCamera->center.y, mCamera->center.z,
		mCamera->up.x, mCamera->up.y, mCamera->up.z); //where to look in the scene


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
}

void HelloGL::Mouse(int button, int state, int x, int y)
{
	if (button == 3)
	{
		mCamera->eye.z += 0.1;
	}

	if (button == 4)
	{
		mCamera->eye.z -= 0.1;
	}
}


