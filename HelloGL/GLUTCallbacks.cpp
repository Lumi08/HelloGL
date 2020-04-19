//Includes
#include "GLUTCallbacks.h"
#include "HelloGL.h"

//Namespacc implementation
namespace GLUTCallbacks
{
	namespace
	{
		HelloGL* helloGl = nullptr;
	}

	void Init(HelloGL* gl)
	{
		helloGl = gl;
	}

	void Display()
	{
		if (helloGl != nullptr)
		{
			helloGl->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		if (helloGl != nullptr)
		{
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			helloGl->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(preferredRefresh - updateTime, Timer, preferredRefresh);
		}
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		if (helloGl != nullptr)
		{
			helloGl->Keyboard(key, x, y);
		}
	}

	void Mouse(int button, int state, int x, int y)
	{
		if (helloGl != nullptr)
		{
			helloGl->Mouse(button, state, x, y);
		}
	}
}