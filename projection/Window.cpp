#include "Window.h"
#include <highgui\highgui_c.h>
#include <assert.h>

using namespace std;
using namespace BasicCvApi;

Window::Window(void)
{
}


Window::~Window(void)
{
	cvDestroyWindow(windowName.c_str());
}

BasicCvApi::Window::Window( const char* m_name ):windowName(m_name)
{
	SetWindow();
}

BasicCvApi::Window::Window( const std::string name ):windowName(name)
{
	SetWindow();
}

void BasicCvApi::Window::show( const IplImage* image, int waitTime )
{
	(image != NULL);
	cvShowImage(windowName.c_str(), image);
	cvWaitKey(waitTime);
}

void BasicCvApi::Window::SetWindow()
{
	cvNamedWindow(windowName.c_str(),1);
}
