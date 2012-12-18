#pragma once

#ifndef Saver_h__
#define Saver_h__

#include <cv.h>
#include <string>

class Saver
{
public:
	Saver(void);
	Saver(std::string path);
	virtual void saveImage(IplImage* iamge,std::string name);
	~Saver(void);
private:
	std::string m_path;

};

#endif // Saver_h__