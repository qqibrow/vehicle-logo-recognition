#ifndef common_h__
#define common_h__

#include <cv.h>


struct Section
{
	Section();
	Section(int,int);
	int start;
	int end;
};

struct Boundary
{
	Boundary();
	Boundary(int m_min, int m_max);
	int min;
	int max;
};


extern bool pointsEqualsTo(const CvPoint& p1, const CvPoint& p2);


#endif // common_h__
