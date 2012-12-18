#include "DataBaseController.h"
#include "dir.h"
#include <cv.h>
#include "SiftFeature.h"
#include "SIFTController.h"
#include <highgui\highgui_c.h>

DataBaseController::DataBaseController(void)
{
}

DataBaseController::DataBaseController( std::string path ):path(path)
{

}


DataBaseController::~DataBaseController(void)
{
}

void DataBaseController::loadInData( std::vector<temlateLogo>& database )
{
	vector<string> files = dir::readImages(path.c_str());
	SIFT::SIFTController siftController;
	path.append("\\");
	string fullpath;
	//SIFT::SiftFeature feat;
	

	vector<string>::iterator it;
	for ( it = files.begin(); it< files.end(); it++)
	{
		fullpath = path + *it;
		IplImage* logo = cvLoadImage(fullpath.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
		BasicCvApi::MyImagePtr imagePtr(logo);
		database.push_back(temlateLogo(siftController.getImgSIFTFeature(logo),*it, imagePtr));
	}
}
