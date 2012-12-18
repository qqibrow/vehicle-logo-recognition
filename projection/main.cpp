#include <iostream>
#include <cv.h>
#include <highgui\highgui_c.h>
#include <string>
#include <fstream>
#include "Window.h"
#include "verticalProjection.h"
#include "HorizontalProjection.h"
#include "DIPController.h"
#include "MyImage.h"
#include "DataBaseController.h"
#include "CarLogoDetector.h"
#include "dir.h"
#include "Saver.h"

#include <boost/smart_ptr.hpp>
#include <boost/timer.hpp>

using namespace std;
using namespace BasicCvApi;
using namespace boost;

//////////////////////////////////////////////////////////////////////////
// if define DETECT, output the logo class
//otherwise, it will save the coarse car logo to the directory
// for the test
//////////////////////////////////////////////////////////////////////////

#define  DETECT

int main(int argc,char *argv[])
{

	if (argc != 4)
	{
		printf("error input string\n");
		exit(0);
	}

	string filesLocation(argv[1]),saveDirectory(argv[2]),templateLocation(argv[3]);

	CarLogoDetector detector;
	DataBaseController* databaseController = new DataBaseController(templateLocation);

	


	//load in the locations
	vector<string> files = dir::readImages(filesLocation.c_str());
	filesLocation.append("\\");
	saveDirectory.append("\\");
	string fullpath;
	string saveLoc;
	
	vector<string>::iterator it;

	string fileOutput = filesLocation + saveDirectory + "z.out";
	ofstream fout(fileOutput);

	//load in the data

	boost::timer timer;
#ifdef DETECT	
	detector.initDataBase(databaseController);	
	fout<<"init database success"<<endl<<"time: "<<timer.elapsed()<<"s"<<endl;
	cout<<"init database success"<<endl<<"time: "<<timer.elapsed()<<"s"<<endl;
#endif
	

	fout<<"there are totally "<<files.size()<<" images"<<endl;

	string className;
	Saver* saver = new Saver(string(filesLocation + saveDirectory));

	for ( it = files.begin(); it< files.end(); it++)
	{
		timer.restart();
		fout<<"//////////////////////////////////////////////////////////////////////////"<<endl;
		fout<<"current file: "<<*it <<endl;
		cout<<"current file: "<<*it <<endl;

		fullpath = filesLocation + *it;
		saveLoc = filesLocation + saveDirectory + *it;
		IplImage* image = cvLoadImage(fullpath.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
		BasicCvApi::MyImagePtr imagePtr(image);

		// get the coarse logo 
		IplImage* logo = detector.getCoarseLogoAreaFromImage(image);
		

	#ifdef DETECT
	//show coarse result
		//Window m_window(*it);
		//m_window.show(logo,0);

		// detect the coarse logo
		className = detector.detectLogoImage(logo);
		if(className != "no")
		{
			detector.outputTextResult(fout);
			detector.saveResultsImgs(saver);
		}
		


		fout<<"final className: "<<className<<endl
			<<"timer "<<timer.elapsed()<<"s"<<endl;

		
#endif
		cout<<"still "<<files.end() - it <<" files..."<<endl;

#ifndef DETECT
	cvSaveImage(saveLoc.c_str(), logo,0);
#endif
	}
	cout<<"OK"<<endl;
	fout.close();
 	 return 0;
}