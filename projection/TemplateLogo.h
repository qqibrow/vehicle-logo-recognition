#ifndef TemplateLogo_h__
#define TemplateLogo_h__

#include "SiftFeature.h"
#include "MyImage.h"
#include <string>


class temlateLogo
{	
public:
	temlateLogo();
	temlateLogo(SIFT::SiftFeature feat, std::string name, BasicCvApi::MyImagePtr ptr);
	SIFT::SiftFeature siftfeat;
	std::string className;
	BasicCvApi::MyImagePtr ptr;
};











#endif // TemplateLogo_h__
