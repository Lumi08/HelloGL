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
			helloGl->Update();
			glutTimerFunc(preferredRefresh, Timer, preferredRefresh);
		}
	}
}