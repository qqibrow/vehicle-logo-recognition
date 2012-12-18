#include "HorizontalProjection.h"
#include <algorithm>
#include <cv.h>
using namespace BasicCvApi;


HorizontalProjection::HorizontalProjection(void)
{
}


HorizontalProjection::~HorizontalProjection(void)
{
}

void BasicCvApi::HorizontalProjection::calculateProj( vector<int> & data, Boundary b /*= Boundary(0,0)*/ )
{
	assert(orignImage != NULL);
	int left,right;

	if ( 0 == b.min && 0 == b.max)
	{
		left = 0;
		right = orignImage->width;
	}
	else
	{
		left = b.min;
		right = b.max;
	}

	assert( left >= 0 && left < right && right <= orignImage->width);

	int x,y;
	CvScalar s;

	for( y=0;y<orignImage->height;y++)
	{  
		for( x=left;x<right;x++)
		{   
			s=cvGet2D(orignImage,y,x);    //t=cvGet2D(paint,y,x);       
			if(s.val[0]==255)    
				data[y]++;         
		}    
	}
}

void BasicCvApi::HorizontalProjection::setDataImagewithBackground( const IplImage* background, const vector<int> & data)
{
	assert(data.size() <= background->height);
	int x,y;
	CvScalar t;
	graphImage = cvCreateImage(cvGetSize(background),background->depth, background->nChannels);
	cvCopy(background, graphImage);

	for(y=0;y<background->height;y++)
	{  
		for(x=0;x<data[y];x++)
		{   
			t=cvGet2D(graphImage,y,x);   //s=cvGet2D(paint,y,x);    //t=cvGet2D(paint,y,x); 
			t.val[0]=0;   
			cvSet2D(graphImage,y,x,t);        
		}    
	}
}


void BasicCvApi::HorizontalProjection::drawSection( Section section )
{
	cvLine(graphImage,cvPoint(0,section.start),cvPoint(graphImage->width-1, section.start),cvScalar(0,0,0));
	cvLine(graphImage,cvPoint(0,section.end),cvPoint(graphImage->width-1, section.end),cvScalar(0,0,0));
}

BasicCvApi::HorizontalProjection::HorizontalProjection( IplImage* image ):ProjGraph(image)
{

}
