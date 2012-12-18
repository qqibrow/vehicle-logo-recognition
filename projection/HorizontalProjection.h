#pragma once

#ifndef HorizontalProjection_h__
#define HorizontalProjection_h__



#include "ProjGraph.h"

namespace BasicCvApi
{
	class HorizontalProjection :
		public ProjGraph
	{
	public:
		HorizontalProjection(void);
		HorizontalProjection(IplImage* image);
		virtual ~HorizontalProjection(void);
		virtual void calculateProj(vector<int> & data, Boundary b = Boundary(0,0));
		virtual void drawSection(Section section);
		virtual void setDataImagewithBackground( const IplImage* background, const vector<int> & data);
	private:
		
	};

}

#endif // HorizontalProjection_h__