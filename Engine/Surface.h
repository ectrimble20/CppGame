#pragma once
#include "Colors.h"
#include <string>
#include "ChiliWin.h"
#include <fstream>
#include "ImageLibrary.h"

class Surface
{
public:
	Surface(int width, int height);
	Surface(const Surface&); //copy constructor
	Surface& operator=(const Surface&);
	Surface(const std::string& bitmapFilename);
	Surface(BitmapImage imageData);
	~Surface();
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const { return width; };
	int GetHeight() const { return height; };
private:
	Color* pPixels = nullptr;
	int width;
	int height;
	bool autoDeleteImagePointerData = true;
};

