#include "Graph.h"

using namespace BasicCvApi;
using namespace std;

Graph::Graph(void):graphImage(NULL)
{
}


Graph::~Graph(void)
{
}

void BasicCvApi::Graph::show( BasicCvApi::Window& window )
{
	assert(graphImage != NULL);
	window.show(graphImage,0);
}

IplImage* BasicCvApi::Graph::getGraphImage() const
{
	return graphImage;
}

void BasicCvApi::Graph::saveImage( Saver* saver, string name) const
{
	saver->saveImage(this->graphImage, name);
}
