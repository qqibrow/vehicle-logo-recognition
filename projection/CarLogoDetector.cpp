#include "CarLogoDetector.h"
#include "DIPController.h"
#include "HorizontalProjection.h"
#include "verticalProjection.h"
#include "MyImage.h"
#include "Array1D.h"
#include "Window.h"
#include "ProjGraph.h"
#include "SIFTController.h"
#include <algorithm>
#include <boost/smart_ptr.hpp>

using namespace BasicCvApi;
using namespace boost;

CarLogoDetector::CarLogoDetector(void)
{
}


CarLogoDetector::~CarLogoDetector(void)
{
}

void CarLogoDetector::initDataBase(DataBaseController* imageLoader)
{
	imageLoader->loadInData(this->templateImages);
}


// this will show every image after every step
//#define SHOWRESULT


IplImage* CarLogoDetector::getCoarseLogoAreaFromImage(IplImage* image )
{
	//首先对图像进行处理，缩小图像和提取canny边缘图像
	DIPController imageProcessing;
	MyImagePtr smallerImg(imageProcessing.getScaleImage(image,0.5));
	MyImagePtr cannyImg(imageProcessing.getCannyImage(smallerImg.get()));

	//show result
	#ifdef SHOWRESULT
Window canny("cannyImg");
	canny.show(cannyImg.get(),0);
#endif
	//1. get the vertical projection and calculate the left and right of the car

	boost::shared_ptr<ProjGraph> vertical(new VerticalProjection(cannyImg.get()));
	vector<int> xArray(cannyImg->width);

	// calculate vertical projection
	vertical->calculateProj(xArray);

	// warp it to get the right and left using the ProjArray class
	ProjArray verticalArray(xArray);
	Boundary b(Prior_left, Prior_right);
	Section leftAndRight = verticalArray.getLongtestNeighborLength(NEIGHBOUR_DIST,b);
	
	// input the background and the vertical projection to get the projection image
	vertical->getBackground(smallerImg.get(),xArray);
	vertical->drawSection(leftAndRight);

	//show result
#ifdef SHOWRESULT
	BasicCvApi::Window verticalImg("verticalProjection");
	vertical->show(verticalImg);
#endif

	// get background image and put it in the horizontal projection image
	IplImage* tempBack = vertical->getGraphImage();


	boost::shared_ptr<ProjGraph> horizontal(new HorizontalProjection(cannyImg.get()));
	vector<int> yArray(cannyImg->height);
	horizontal->calculateProj(yArray,Boundary(leftAndRight.start,leftAndRight.end));
	ProjArray HorizontalArray(yArray);

	Section upandDown = HorizontalArray.getUpAndDown();

	horizontal->getBackground(tempBack,HorizontalArray.getData());
	horizontal->drawSection(upandDown);
#ifdef SHOWRESULT
	
	BasicCvApi::Window horizonW("horizonProjection");
	horizontal->show(horizonW);
#endif
	// will return the whole graph image
	//return horizontal->getGraphImage();

	return imageProcessing.getSubImage(image, leftAndRight, upandDown);	
}

std::string CarLogoDetector::detectLogoImage( IplImage* image )
{
	BasicCvApi::MyImagePtr imagePtr(image);
	SIFT::SIFTController siftController;
	
	
	vector<temlateLogo>::iterator it = templateImages.begin();

	SIFT::SiftFeature imageFeature = siftController.getImgSIFTFeature(image);

	int max = 0;
	int response;
	int index = -1;

	clear();

	for(; it != templateImages.end(); it++)
	{
		response = siftController.getSIFTmatchResponse(imageFeature, it->siftfeat);

		if (response != 0)
		{
			responses.push_back(response);
			IplImage* resultImg = siftController.setResultImg(it->ptr.get(),image);
			resultImgs.push_back(BasicCvApi::MyImagePtr(resultImg));
			strings.push_back(it->className);
		}

		if(response > max)
		{
			max = response;
			index = it - templateImages.begin();
		}
	}

	if(max == 0)
	{
		return string("no");
	}
	else
		return templateImages[index].className;

}

void CarLogoDetector::saveResultsImgs( Saver* saver )
{
	//static int i = 1;
	assert(!resultImgs.empty());

	for(vector<BasicCvApi::MyImagePtr>::iterator it = resultImgs.begin(); it != resultImgs.end(); it++)
	{
		saver->saveImage(it->get(),strings[it-resultImgs.begin()]);
	}
//	++i;
}

void CarLogoDetector::clear()
{
	this->resultImgs.clear();
	this->responses.clear();
	strings.clear();
}

void CarLogoDetector::outputTextResult( std::ofstream& fout )
{
	assert(!strings.empty() && strings.size() == responses.size() && "strings size not equals to response size");
	for( int i = 0; i < strings.size(); i++)
	{
		fout<<strings[i]<<" response: "<<responses[i]<<endl;
	}
}
