#include "verticalProjection.h"
#include "ProjGraph.h"

using namespace BasicCvApi;

VerticalProjection::VerticalProjection(void)
{
}


VerticalProjection::~VerticalProjection(void)
{
}



void BasicCvApi::VerticalProjection::setDataImagewithBackground( const IplImage* background, const vector<int> & data)
{
	assert( data.size() <= background->width );

	//这里用那个只能指针的东西搞一个sizeequal的重载
	//assert()

	int x,y;
	CvScalar t;
	graphImage = cvCreateImage(cvGetSize(background),background->depth, background->nChannels);
	cvCopy(background, graphImage);

	for(x=0;x<graphImage->width;x++)
	{  
		for(y=0;y<data[x];y++)
		{   
			t=cvGet2D(graphImage,y,x);   //s=cvGet2D(paint,y,x);    //t=cvGet2D(paint,y,x); 
			t.val[0]=BLACK;   
			cvSet2D(graphImage,y,x,t);         
		}   
	}
}

void BasicCvApi::VerticalProjection::drawSection( Section section )
{
	cvLine(graphImage,cvPoint(section.start,0),cvPoint(section.start,graphImage->height-1),cvScalar(0,0,0));
	cvLine(graphImage,cvPoint(section.end,0),cvPoint(section.end,graphImage->height-1),cvScalar(0,0,0));

}

void BasicCvApi::VerticalProjection::calculateProj( vector<int> & data, Boundary b /*= Boundary(0,0)*/ )
{
	assert(orignImage != NULL);
	int up,down;

	if ( 0 == b.min && 0 == b.max)
	{
		up = 0;
		down = orignImage->height;
	}
	else
	{
		up = b.min;
		down = b.max;
	}

	assert( up >= 0 && up < down && down <= orignImage->height);

	int x,y;
	CvScalar s;
	for( x=0;x<orignImage->width;x++)      
	{  
		for(y=up; y<down; y++)
		{  
			s=cvGet2D(orignImage,y,x);    //t=cvGet2D(paint,y,x);       
			if(s.val[0]==WHITE)    
				data[x]++;     //cvSet2D(paint,y,x,t);        
		}    
	}
}

BasicCvApi::VerticalProjection::VerticalProjection( IplImage* image ):ProjGraph(image)
{

}
