#include "SIFTController.h"
 #include "sift.h"
 #include "kdtree.h"
#include "utils.h"
#include <vector>
#include "common.h"
#include "Window.h"

using namespace SIFT;
using namespace std;


double SIFT::SIFTController::NN_SQ_DIST_RATIO_THR = 0.49;

SIFTController::SIFTController(void)
{
}


SIFTController::~SIFTController(void)
{
}

SIFT::SiftFeature SIFT::SIFTController::getImgSIFTFeature( IplImage* image )
{
	SiftFeature feature;
	feature.num = sift_features(image, &feature.feat);
	return feature;
}

int SIFT::SIFTController::getSIFTmatchResponse( SIFT::SiftFeature templateFeature, SIFT::SiftFeature feature )
{

	// build the kd root
	struct kd_node* kd_root = kdtree_build( templateFeature.feat, templateFeature.num );
	struct feature* temp;
	struct feature** nbrs;

	points1.clear();
	points2.clear();
	
	int m = 0;
	for(int i = 0; i < feature.num; i++ )
	{
		temp = feature.feat + i;
		int k = kdtree_bbf_knn( kd_root, temp, 2, &nbrs, KDTREE_BBF_MAX_NN_CHKS );

		if(k == -1)  //error
			return 0;

		if( k == 2 )
		{
			double d0 = descr_dist_sq( temp, nbrs[0] );
			double d1 = descr_dist_sq( temp, nbrs[1] );
			if( d0 < d1 * NN_SQ_DIST_RATIO_THR )
			{
				CvPoint pt1 = cvPoint( cvRound( temp->x ), cvRound( temp->y ) );
				points1.push_back(pt1);
				CvPoint pt2 = cvPoint( cvRound( nbrs[0]->x ), cvRound( nbrs[0]->y ) );
				points2.push_back(pt2);
				m++;
				feature.feat[i].fwd_match = nbrs[0];
			}
		}
		free( nbrs );
	}
	// check if it is the logo
	if(checkAccordingToCriterias(m, points1, points2))
		return m;
	else
		return 0;
}

bool SIFT::SIFTController::checkAccordingToCriterias( int m, std::vector<CvPoint>& points1, std::vector<CvPoint>& points2 )
{
	return m > MIN_FEATURES && checkIfParallel(points1,points2);
}

bool SIFT::SIFTController::checkIfParallel( std::vector<CvPoint>& points1, std::vector<CvPoint>& points2 )
{
	if ( pointsAllTheSame(points1) || pointsAllTheSame(points2) )
	return false;
	
	// check if parallel

	return true;
}

bool SIFT::SIFTController::pointsAllTheSame( std::vector<CvPoint>& points )
{
	vector<CvPoint>::iterator it = points.begin();
	CvPoint p = *it;
	
	int m = points.size();
	for(; it != points.end(); it++)
	{
		if (pointsEqualsTo(*it, p))
		m--;
	}

	if ( m == 0)
		return true;

	return false;
}

IplImage* SIFT::SIFTController::setResultImg( IplImage* img1, IplImage* img2 )
{
	assert( !points1.empty() && !points2.empty() && points1.size() == points2.size() && "wrong?");

	IplImage* stacked = stack_imgs( img1, img2 );

// 	BasicCvApi::Window m_window("result");
// 	m_window.show(stacked,0);

	CvPoint pt1,pt2;
	for(int i = 0; i < points1.size(); i++)
	{
		pt1 = points1[i];
		pt2 = points2[i];
		pt2.y += img1->height;
		cvLine( stacked, pt1, pt2, CV_RGB(255,0,255), 1, 8, 0 );
	}
	return stacked;
}
