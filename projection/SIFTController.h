#pragma once


#ifndef SIFTController_h__
#define SIFTController_h__

#include "SiftFeature.h"
#include "MyImage.h"
namespace SIFT
{
	class SIFTController
	{
	public:
		SIFTController(void);
		//************************************
		// CreateTime: 3/15/2012 
		// Description: get the SIFT feature
		// Modified History: 
		//************************************
		SIFT::SiftFeature getImgSIFTFeature(IplImage* image);
		//************************************
		// CreateTime: 3/15/2012 
		// Description: match two SIFT features return responsee
		// Modified History: 
		//************************************
		int getSIFTmatchResponse(SIFT::SiftFeature feat1, SIFT::SiftFeature feat2);
		//************************************
		// CreateTime: 3/15/2012 
		// Description: create match image
		// Modified History: 
		//************************************
		IplImage* setResultImg(IplImage* img1, IplImage* img2);
		~SIFTController(void);		
	private:
		bool checkAccordingToCriterias(int m, std::vector<CvPoint>& points1, std::vector<CvPoint>& points2 );

		// not implemented
		bool checkIfParallel( std::vector<CvPoint>& points1, std::vector<CvPoint>& points2 );

		bool pointsAllTheSame( std::vector<CvPoint>& points );
		
	
		enum{KDTREE_BBF_MAX_NN_CHKS = 200,
			M_MIN = 2,MIN_FEATURES = 3,
		};
		static double NN_SQ_DIST_RATIO_THR;
	private:
		//the start points and end points of those matched lines, bad design
		std::vector<CvPoint> points1;
		std::vector<CvPoint> points2;
	};

}


/*static double SIFTController::NN_SQ_DIST_RATIO_THR = 0.49;*/

#endif // SIFTController_h__