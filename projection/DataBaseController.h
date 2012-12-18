#pragma once
#include <vector>
#include "TemplateLogo.h"

// virtual function loadInData can be derived for change 
class DataBaseController
{
public:
	DataBaseController(void);
	DataBaseController(std::string path);
	virtual void loadInData(vector<temlateLogo>& database);
	~DataBaseController(void);
private:
	std::string path;
};

