#pragma once
#include "Colors.h"
#include <string>
#include "ChiliWin.h"
#include <fstream>
#include <map>
#include <iterator>
#include "GameLogger.h"
#include "StructLib.h"


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

