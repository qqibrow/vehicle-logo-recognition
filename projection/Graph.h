#pragma once

#ifndef Graph_h__
#define Graph_h__



#include <cv.h>
#include "Window.h"
#include "Saver.h"
#include <string>
namespace BasicCvApi
{

	class Graph
	{
	public:
		Graph(void);
		~Graph(void);

		//************************************
		// CreateTime: 3/15/2012 
		// Description: use the window to show graph image
		// Modified History: 
		//************************************
		void show( Window& window);
		//************************************
		// CreateTime: 3/15/2012 
		// Description: use the saver to save image
		// Modified History: 
		//************************************
		void saveImage( Saver* saver, std::string name) const;
		//************************************
		// CreateTime: 3/15/2012 
		// Description: sometimes i need to pass graph the image to others( may be not a good design)
		// Modified History: 
		//************************************
		IplImage* getGraphImage() const;
	protected:
		IplImage* graphImage; 
	};

}

#endif // Graph_h__