#include "DIPController.h"
#include "MyImage.h"

DIPController::DIPController(void)
{
}


DIPController::~DIPController(void)
{
}

IplImage* DIPController::getScaleImage( const IplImage* image, float scale )
{
	IplImage* dst = cvCreateImage(cvSize(image->width*scale, image->height*scale),image->depth, image->nChannels);
	cvResize( image, dst, CV_INTER_LINEAR );
	return dst;
}

IplImage* DIPController::getCannyImage( const IplImage* image )
{
	IplImage* dst = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, image->nChannels);
	BasicCvApi::MyImagePtr smoothImgPtr(getSmoothImage(image));
	cvCanny(smoothImgPtr.get(), dst,60,150,3);
	return dst;
}

IplImage* DIPController::getSmoothImage( const IplImage* image )
{
	IplImage* smoothImg = cvCreateImage(cvSize(image->width, image->height),IPL_DEPTH_8U, image->nChannels);
	cvSmooth(image,smoothImg,CV_MEDIAN,3,0);
	return smoothImg;
}

IplImage* DIPController::getSubImage( IplImage* image, Section leftAndRight, Section upAndDown )
{
	int x = leftAndRight.start;
	int y = upAndDown.start;
	int w = leftAndRight.end - leftAndRight.start;
	int h = upAndDown.end - upAndDown.start;

	int middle_X = x + w/2 - LOGO_HALF_W;
	int middle_w = 2*LOGO_HALF_W;

	cvSetImageROI(image, 
		cvRect(2*middle_X, 2*y, 2*middle_w, 2*h)
		);
	IplImage* lightZone = cvCreateImage(cvGetSize(image), image->depth,image->nChannels);
	cvCopy(image, lightZone,NULL);

	return lightZone;

}
