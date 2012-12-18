#include "Array1D.h"
#include <algorithm>

using namespace std;

class TestPoint
{
public:
	TestPoint();
	TestPoint( int s, int a);
	int start;
	int area;
	bool operator<( const TestPoint& rhs ) const;
};

bool TestPoint::operator<( const TestPoint& rhs ) const
{
	return this->area < rhs.area;
}

TestPoint::TestPoint():start(0),area(0)
{

}

TestPoint::TestPoint( int s, int a ):start(s),area(a)
{

}

ProjArray::ProjArray(void)
{
}

ProjArray::ProjArray( int* data, int length )
{
	for(int i = 0; i < length; i++)
	{
		this->data.push_back(data[i]);
	}
}

ProjArray::ProjArray( vector<int>& data ):data(data.begin(), data.end())
{
}


ProjArray::~ProjArray(void)
{
}

Section ProjArray::getLongtestNeighborLength( int neighborDist, Boundary boundary )
{

	Section finalResult,tempResult, temp;
	int min_boundary(boundary.min),max_boundary(boundary.max-1);
	int i(min_boundary),j;

	while( i < max_boundary)
	{
		if( i == min_boundary ||(0 == data[i] && 0 != data[i+1]))   // i  满足先验条件
		{

			temp.start = i;
			for( j = i; j < max_boundary && !( 0 != data[j] && 0 == data[j+1] ); j++);
			temp.end = j;

			if (tempResult.start == 0 && tempResult.end == 0)  //temp 为 空
			{
				tempResult = temp;
			}			
			else if ( temp.start - tempResult.end <= neighborDist)
			{
				tempResult.end = temp.end;
			}
			else
			{
				//if finalresult == 0, finalResult = tempResult, tempResult = temp;
				if ( finalResult.start == 0 && finalResult.start == 0)
				{
					finalResult = tempResult;

				}			
				else if ( tempResult.end - tempResult.start >= finalResult.end - finalResult.start)
				{
					finalResult = tempResult;

				}
				tempResult = temp;
			}
			i = j;
		}
		else
			i++;

	}

	if ( tempResult.end - tempResult.start >= finalResult.end - finalResult.start)
	{
		finalResult = tempResult;

	}

	return finalResult;
}

int ProjArray::calculateContinueArea( int start, int width ) const
{
	int sum = 0;
	for( int i = start; i < start + width; i++)
	{
		sum += data[i];	
	}
	return sum;
}

void ProjArray::smooth( int winsize )
{
	assert( winsize %2 != 0);   // make sure winsize is not even
	int halfsize = (winsize - 1)/2;
	for( int i = halfsize; i < data.size() - halfsize; i++)
	{
		int sum = 0;
		for( int j = i - halfsize; j <= i + halfsize; j++)
			sum += data[j];

		data[i] = sum/winsize;
	}
}

bool CompareIterator(vector<int>::iterator & lhs, vector<int>::iterator & rhs)
{
	return *lhs < *rhs;
}


Section ProjArray::getUpAndDown()
{
	// find the median
	vector<vector<int>::iterator> its;
	for( vector<int>::iterator it = data.begin(); it != data.end(); it++)
	{
		its.push_back(it);
	}

	nth_element(its.begin(), its.begin() + its.size()*0.50, its.end(),CompareIterator);

	vector<int> values;
	int median = **(its.begin() + its.size()*0.50);

// 	for( vector< vector<int>::iterator>::iterator it = its.begin(); it != its.end(); it++)
// 	{
// 		values.push_back(**it);
// 	}

	vector<TestPoint> points;
	for ( int i = 150; i < data.size() - LIGHTZONE_WIDTH; i++)
	{
		if ( data[i] > median)
		{
			points.push_back(TestPoint(i, calculateContinueArea(i,LIGHTZONE_WIDTH)));
		}
	}
	//vector<TestPoint>::iterator maxPoint = max_element(points.begin(),points.end());
	//Section section(maxPoint->start,maxPoint->start + LIGHTZONE_WIDTH);

	int d = 0;
	data.assign(data.size(),0);
	if( points.size() < 10)
	{
		for( vector<TestPoint>::iterator it = points.begin(); it != points.end(); it++)
		{
			d += it->start;
			data[it->start] = it->area/10;
		}
		d = d / points.size();
	}
	else
	{
		vector<TestPoint>::iterator left25percent = points.end() - 10;
		nth_element( points.begin(), left25percent, points.end());
		for( vector<TestPoint>::iterator it = left25percent; it != points.end(); it++)
		{
			d += it->start;		
			data[it->start] = it->area/10;
			

		}
		d= d/10;
	}

// 	vector<TestPoint>::iterator left25percent = points.begin() + 10;
// 	nth_element( points.begin(), left25percent, points.end());
// 
// 	data.assign(data.size(),0);
// 	for( vector<TestPoint>::iterator it = left25percent; it != points.end(); it++)
// 	{
// 		if (it->start > 150)
// 		{
// 			data[it->start] = it->area/10;
// 		}
// 		
// 	}


	return Section(d,d + LIGHTZONE_WIDTH);
}

vector<int> ProjArray::getData() const
{
	return vector<int>(this->data.begin(), this->data.end());
}

