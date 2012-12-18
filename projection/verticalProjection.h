#pragma once
#include "projgraph.h"
#include "common.h"
#ifndef verticalProjection_h__
#define verticalProjection_h__



namespace BasicCvApi
{
	class VerticalProjection :
		public ProjGraph
	{
	public:
		VerticalProjection(void);
		VerticalProjection(IplImage* image);
		virtual ~VerticalProjection(void);
		virtual void setDataImagewithBackground(const IplImage* background, const vector<int> & data);
		virtual void calculateProj(vector<int> & data, Boundary b = Boundary(0,0));
		virtual void drawSection( Section section );

	};

}

#endif // verticalProjection_h__

