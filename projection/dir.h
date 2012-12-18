#pragma once
#include <cstdlib>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// just used to load images in directory
// thanks to the writer,sorry, I forget your name


namespace dir
{
	vector<string> getSubfolders( LPCSTR path);
	vector<string> readFiles( LPCSTR path);

	vector<string> readImages(LPCSTR path);

	wstring string2wstring(const string& str);
	string    wstring2string(const wstring& wstr);

	string changeFileExt(const string& path,const string& ext);
};
