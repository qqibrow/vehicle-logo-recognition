#pragma once

#ifndef Array1D_h__
#define Array1D_h__

#include <vector>
#include "common.h"

class ProjArray
{
public:

	ProjArray(void);
	ProjArray(int* data, int length);
	ProjArray(vector<int>& data);
	//************************************
	// CreateTime: 3/15/2012 
	// Description: get the longest continual nonzero section
	// @neighborDist: in order to cross short zero part
	// @boundary: the start and end
	// Modified History: 
	//************************************
	Section getLongtestNeighborLength(int neighborDist, Boundary boundary);
	//************************************
	// CreateTime: 3/15/2012 
	// Description: get the up and down in the horizontal projection data(not a good name, need refact)
	// Modified History: 
	//************************************
	Section getUpAndDown();
	//************************************
	// CreateTime: 3/15/2012 
	// Description: return the data, because i need it to put in the ProjGraph and get Graph image
	// not a good design
	// or I could add a interface in Graph, but I need to let ProjGraph become ProjArray's friend
	// I think current design is better because in my opinion, friend is not a good sign
	// Modified History: 
	//************************************
	vector<int> getData() const;
	~ProjArray(void);
private:
	int calculateContinueArea(int start, int width) const;
	void smooth(int winsize);

	std::vector<int> data;
	enum{LIGHTZONE_WIDTH = 50};
};




#endif // Array1D_h__