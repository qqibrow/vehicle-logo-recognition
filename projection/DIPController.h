#pragma once

#ifndef DIPController_h__
#define DIPController_h__

#include <cv.h>
#include "common.h"
class DIPController
{
public:
	DIPController(void);
	IplImage* getScaleImage(const IplImage* image, float scale);
	IplImage* getCannyImage(const IplImage* image);
	~DIPController(void);
	IplImage* getSmoothImage( const IplImage* image );
	IplImage* getSubImage(IplImage* image, Section leftAndRight, Section upAndDown);
private:
	enum{ LOGO_HALF_W = 35};

};


#endif // DIPController_h_