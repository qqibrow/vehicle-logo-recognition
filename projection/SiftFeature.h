#include "imgfeatures.h"


#ifndef SiftFeature_h__
#define SiftFeature_h__

namespace SIFT
{
	struct SiftFeature
	{
		int num;
		struct feature* feat;
	};
}


#endif // SiftFeature_h__