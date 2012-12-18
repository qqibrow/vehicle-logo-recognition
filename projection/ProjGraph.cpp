#include "ProjGraph.h"

using namespace BasicCvApi;

ProjGraph::ProjGraph(void):orignImage(NULL)
{
}


ProjGraph::~ProjGraph(void)
{
	
}

void ProjGraph::setImage(IplImage* orignImage )
{
	this->orignImage = orignImage;
}


BasicCvApi::ProjGraph::ProjGraph( IplImage* orignImage )
{
	this->setImage(orignImage);
}

void BasicCvApi::ProjGraph::getBackground( const IplImage* background, const vector<int>& data )
{
	assert(background != NULL && orignImage != NULL && orignImage->imageSize == background->imageSize);
	this->setDataImagewithBackground(background,data);
}
