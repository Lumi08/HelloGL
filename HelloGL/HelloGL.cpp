#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	mRotation = 0.0f;
	
	mCamera = new Camera();
	mCamera->eye = Vector3{ 0.0f, 0.0f, 1.0f };
	mCamera->center = Vector3{ 0.0f, 0.0f, 0.0f };
	mCamera->up = Vector3{ 0.0f, 1.0f, 0.0f };


	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
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
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{

}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(mRotation, -1.0f, -1.0f, -1.0f);

	glutWireTeapot(1);
	
	glBegin(GL_POLYGON);
		/*glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.75, 0.5);
		glVertex2f(0.75, 0.5);
		glVertex2f(0.75, -0.5);
		glVertex2f(-0.75, -0.5);*/
	glEnd();

	glPopMatrix();

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
	if (key == 'd')
	{
		mRotation += 0.5f;
	}
}
