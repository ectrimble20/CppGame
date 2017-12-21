#pragma once
#include "Colors.h"
#include <string>
#include "ChiliWin.h"
#include <fstream>
#include <map>
#include <iterator>
#include "GameLogger.h"

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

class ImageLibrary
{
public:
	ImageLibrary();
	~ImageLibrary();
	void ImportSingleImage(std::string imageKey, std::string imagePath);
	void ImportSpriteSheet(std::string imagePath, SpriteSheetCell * sheetCellInformation, int numberOfCells);
	//bool ImportSpriteMap(); //need to think this one over
	//bool ImportImageFromSpriteMap(std::string imageKey, std::string imagePath, int imageX, int imageY, int imageWidth, int imageHeight);
	BitmapImage SeekImage(std::string imageKey);
	void CopyImageReplaceColor(std::string imageKey, std::string newImageKey, Color colorToReplace, Color replaceWithColor);
private:
	//std::map<std::string, Color*> images; //replaced by struct
	std::map<std::string, BitmapImage> images;
	void loadImageIntoMap(BitmapImage imageInfo);
	void deleteImage(std::string imageKey);
	//This function loads anything we want preloaded just by creating the image class
	//Add any images wanted here
	void preload();
	void ImportFontImages(std::string fontKey, std::string fontImage, int glyphWidth, int glyphHeight, int columns, int rows);
};

