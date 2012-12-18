#pragma once

#ifndef CarLogoDetector_h__
#define CarLogoDetector_h__

#include <string>
#include "MyImage.h"
#include "Array1D.h"
#include "DIPController.h"
#include "TemplateLogo.h"
#include "DataBaseController.h"
#include "Saver.h"
#include <fstream>

class CarLogoDetector
{
public:
	CarLogoDetector(void);
	//************************************
	// CreateTime: 3/4/2012 
	// Description: to load in the images in the dataBase
	// Modified History: 
	//************************************
	void initDataBase( DataBaseController* imageLoader);
	//************************************
	// CreateTime: 3/5/2012 
	// Description: to get the car logo area
	// it could be combined with the following function
	// but I need to use the coarse logo in test process
	// Modified History: 
	//************************************
	IplImage* getCoarseLogoAreaFromImage(IplImage* image);
	//************************************
	// CreateTime: 3/15/2012 
	// Description:  input the coarse logo image, output the car logo class
	// Modified History: 
	//************************************
	string detectLogoImage(IplImage* image);
	//************************************
	// CreateTime: 3/15/2012 
	// Description: save candidate images, used in test process
	// Modified History: 
	//************************************
	void saveResultsImgs(Saver* saver);
	~CarLogoDetector(void);
	//************************************
	// CreateTime: 3/15/2012 
	// Description: clear all temp variables
	// Modified History: 
	//************************************
	void clear();
	//************************************
	// CreateTime: 3/15/2012 
	// Description:  output candidate name and corresponding response
	// Modified History: 
	//************************************
	void outputTextResult( std::ofstream& fout);
private:
	// save the template image, loaded in by the databaseLoader
	vector<temlateLogo> templateImages;

	// the sift responses
	vector<int> responses;

	// candidate sift match image, used in test process
	vector<BasicCvApi::MyImagePtr> resultImgs;

	// candidate names
	vector<std::string> strings;

	enum{ Prior_left = 130, Prior_right = 600,
	NEIGHBOUR_DIST = 10,};

};




#endif // CarLogoDetector_h__