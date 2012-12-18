#include "TemplateLogo.h"

temlateLogo::temlateLogo():ptr(NULL)
{

}

temlateLogo::temlateLogo( SIFT::SiftFeature feat, std::string name, BasicCvApi::MyImagePtr ptr ):
siftfeat(feat), className(name), ptr(ptr)
{

}