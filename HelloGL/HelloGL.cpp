#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	InitObjects();
	InitGL(argc, argv);
}

void HelloGL::InitObjects()
{
	mRotation = 0.0f;

	mCamera = new Camera();
	mCamera->eye = Vector3{ 0.0f, 0.0f, 1.0f };
	mCamera->center = Vector3{ 0.0f, 0.0f, 0.0f };
	mCamera->up = Vector3{ 0.0f, 1.0f, 0.0f };

	Mesh* cubeMesh = MeshLoader::Load((char*)"Cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"Pyramid.txt");

	for (int i = 0; i < 100; i++)
	{
		mObjects[i] = new Cube(cubeMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
	for (int i = 100; i < 200; i++)
	{
		mObjects[i] = new Cube(pyramidMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{

}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 200; i++)
	{
		mObjects[i]->Draw();
	}

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


	if (key == 'd')
	{
		mCamera->eye.z += 0.1;
	}
}


