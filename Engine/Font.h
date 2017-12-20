#pragma once
#include "ImageLibrary.h"
#include "Surface.h"
#include <string>
#include "Colors.h"

class Font
{
public:
	Font(BitmapImage fontImage);
	~Font();
	Surface StrToSurface(std::string s, Color c);
private:
	void CharToImage(const char c); //this needs to do something meaningful
	//these should be fixed sizes with the font image
	static constexpr char firstChar = ' '; //ASCII 32
	static constexpr char lastChar = '~'; //ASCII 126
	static constexpr int columns = 32;
	static constexpr int rows = 3;
	static constexpr int imageWH = 32; //image width/height, must be a square in this version.
	//Raw Bitmap of our letters
	BitmapImage image;
};

