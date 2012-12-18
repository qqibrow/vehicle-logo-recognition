#pragma once

#ifndef ImageSmartPtr_h__
#define ImageSmartPtr_h__


#include <cv.h>
#include <boost/smart_ptr.hpp>

class ImageSmartPtr: public boost::shared_ptr<IplImage>
{
public:
	ImageSmartPtr(void);
	ImageSmartPtr(IplImage* image);
	virtual ~ImageSmartPtr(void);
};

#endif // ImageSmartPtr_h__