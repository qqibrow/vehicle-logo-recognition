#pragma once
#include "graph.h"

#ifndef ProjGraph_h__
#define ProjGraph_h__

#include "Array1D.h"
#include "Array1D.h"

namespace BasicCvApi
{
	

class ProjGraph :
	public Graph
{
public:
	ProjGraph(void);
	ProjGraph(IplImage* orignImage);
	//************************************
	// CreateTime: 3/15/2012 
	// Description: set the image to be processed, must be a BLACK and WHITE image
	// Modified History: 
	//************************************
	void setImage(IplImage* orignImage);
	//************************************
	// CreateTime: 3/15/2012 
	// Description:  draw the section in the graph image
	// Modified History: 
	//************************************
	virtual void drawSection(Section section) = 0;
	//************************************
	// CreateTime: 3/15/2012 
	// Description:  calculate projection and save the values in vector<int> & data
	// Modified History: 
	//************************************
	virtual void calculateProj(vector<int> & data, Boundary boundary = Boundary(0,0)) = 0;
	//************************************
	// CreateTime: 3/15/2012 
	// Description: use the background and data to draw the graph image
	// Modified History: 
	//************************************
	void getBackground(const IplImage* background, const vector<int>& data);
	virtual ~ProjGraph(void);

	static enum{BLACK = 0, WHITE = 255};

protected:
	IplImage* orignImage;
	virtual void setDataImagewithBackground(const IplImage* background, const vector<int>& data) = 0;
	
};

}

#endif // ProjGraph_h__