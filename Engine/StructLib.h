#pragma once
#include "Colors.h"
#include <string>

/*
StructLib

Central place to keep my struct definitions.
*/


struct BitmapImage
{
	BitmapImage(std::string key, int width, int height, Color * pPixels) : key(key), width(width), height(height), pPixels(pPixels) {};
	bool IsValid() {
		return (width > 0 && height > 0 && key != " " && pPixels != nullptr); //this is what it is set to if it fails by default
	};
	std::string key; //not really used, just for debug/validation if required
	int width;
	int height;
	Color * pPixels;
};

//Represents a single image within a sprite sheet, this is NOT an image itself, but rather
//should be used with the ImportSpriteSheet functionality.  To use this, you'll need to create
//and array of SpriteSheetCells for the particular sprite sheet.
struct SpriteSheetCell
{
	SpriteSheetCell() = default;
	SpriteSheetCell(std::string key, int w, int h, int x, int y) : key(key), width(w), height(h), topLeftX(x), topLeftY(y) {};
	std::string key;
	int width;
	int height;
	int topLeftX; //used to map position on the image to extract a subimage from the sheet
	int topLeftY;
};