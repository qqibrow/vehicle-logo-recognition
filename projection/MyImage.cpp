#include "MyImage.h"

using namespace BasicCvApi;

void BasicCvApi::my_delete(IplImage * p)
{
	cvReleaseImage(&p);
}


BasicCvApi::MyImagePtr::MyImagePtr( IplImage* image ):ImageSmartPtr(image,my_delete)
{

}

BasicCvApi::MyImagePtr::~MyImagePtr()
{

}