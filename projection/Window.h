#pragma once

#ifndef Window_h__
#define Window_h__

#include <string>
#include <cv.h>

// just warp the window fuctions in openCV

namespace BasicCvApi
{
	class Window
	{
	public:
		Window(const char* name);
		Window(const std::string name);
		void show(const IplImage* image, int waitTime);
		~Window(void);
	private:
		Window(void);
		Window& operator=(const Window);
		Window(const Window&);
		void SetWindow();
	private:
		std::string windowName;

	};
}

#endif // Window_h__


