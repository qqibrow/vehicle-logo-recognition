#include "common.h"


Section::Section()
{
	this->start = this->end = 0;
}

Section::Section(int s, int e)
{
	this->start = s;
	this->end = e;
}

Boundary::Boundary():min(0),max(0)
{

}

Boundary::Boundary(int m_min, int m_max):min(m_min),max(m_max)
{

}

bool pointsEqualsTo(const CvPoint& p1, const CvPoint& p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}
