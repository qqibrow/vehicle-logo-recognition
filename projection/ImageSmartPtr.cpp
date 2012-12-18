#include "ImageSmartPtr.h"


ImageSmartPtr::ImageSmartPtr(void)
{
}

ImageSmartPtr::ImageSmartPtr( IplImage* image ):shared_ptr<IplImage>(image)
{

}


ImageSmartPtr::~ImageSmartPtr(void)
{
	IplImage* image = get();
	cvReleaseImage(&image);
}
