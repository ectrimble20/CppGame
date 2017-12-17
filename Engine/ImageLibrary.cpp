#include "ImageLibrary.h"

ImageLibrary::~ImageLibrary()
{
	//since we're storing everything via ptr's on the heap, we need to go through and destroy all the color arrays.
	std::map<std::string, BitmapImage>::iterator i;
	for (i = images.begin(); i != images.end(); i++)
	{
		delete[] i->second.pPixels;
		i->second.pPixels = nullptr;
	}
}

void ImageLibrary::ImportSingleImage(std::string imageKey, std::string imagePath)
{
	std::ifstream bitmapFile(imagePath, std::ios::binary);
	//exit if we failed to open - TODO log this error
	if (!bitmapFile)
	{
		return;
	}
	BITMAPFILEHEADER bitmapFileHeader;
	bitmapFile.read(reinterpret_cast<char*>(&bitmapFileHeader), sizeof(bitmapFileHeader));

	BITMAPINFOHEADER bitmapInfoHeader;
	bitmapFile.read(reinterpret_cast<char*>(&bitmapInfoHeader), sizeof(bitmapInfoHeader));

	bool rowOrderRevered = false;
	bool is32Bit = bitmapInfoHeader.biBitCount == 32;
	int width = bitmapInfoHeader.biWidth;
	int height = bitmapInfoHeader.biHeight;
	int yStart = height - 1;
	int yEnd = 0;
	int deltaY = -1;
	if (height < 0)
	{
		rowOrderRevered = true;
		height = -height; //convert back to a positive number
		yStart = 0;
		yEnd = height;
		deltaY = 1;
	}

	Color * pImg = new Color[width * height];

	bitmapFile.seekg(bitmapFileHeader.bfOffBits);
	const int bitmapPadding = (4 - (width * 3) % 4) % 4;

	//untested
	for (yStart; yStart != yEnd; yStart += deltaY)
	{
		for (int x = 0; x < width; x++)
		{
			//pPixels[(y * width) + x] = c;
			pImg[(yStart * width) + x] = Color(bitmapFile.get(), bitmapFile.get(), bitmapFile.get());
			if (is32Bit)
			{
				bitmapFile.seekg(1, std::ios::cur);
			}
		}
		//only need to adjust padding if it's 24 bit, 32 bit is always aligned
		if (!is32Bit)
		{
			bitmapFile.seekg(bitmapPadding, std::ios::cur);
		}
	}
	BitmapImage image(imageKey, width, height, pImg);
	loadImageIntoMap(image);
}

void ImageLibrary::ImportSpriteSheet(std::string imagePath, SpriteSheetCell * sheetCellInformation, int numberOfCells)
{
	std::string tempKey = "temporary_sprite_sheet_key";
	ImportSingleImage(tempKey, imagePath);
	BitmapImage spriteSheet = SeekImage(tempKey);
	if (!spriteSheet.IsValid())
	{
		//need to log an error/exception or something to indicate this went to shit
	}
	//if we make it here, we know we have a valid image to work with.
	//we can now loop through the sprite sheet cells and load them as individual images
	for (int i = 0; i < numberOfCells; i++)
	{
		SpriteSheetCell spriteInfo = sheetCellInformation[i];
		Color * spriteImage = new Color[spriteInfo.width * spriteInfo.height];
		int startX = spriteInfo.topLeftX;
		int startY = spriteInfo.topLeftY;
		int stopX = spriteInfo.width + startX;
		int stopY = spriteInfo.height + startY;
		int spriteImageIndex = 0;
		for (int y = startY; y < stopY; y++)
		{
			for (int x = startX; x < stopX; x++)
			{
				int pixelCoordinate = (spriteSheet.width * y) + x;
				//spriteImage[(y * spriteInfo.width) + x] =;
				spriteImage[spriteImageIndex] = spriteSheet.pPixels[pixelCoordinate];
				spriteImageIndex += 1;
			}
		}
		//logger.log("Finished iterating on the pixels, performed " + std::to_string(logCountIterations) + ", expected to do " + std::to_string(spriteInfo.width * spriteInfo.height));
		//okay, lets build the BitmapImage
		BitmapImage sprite(spriteInfo.key, spriteInfo.width, spriteInfo.height, spriteImage);
		loadImageIntoMap(sprite);
		//that should do it
	}
	//clean up the sprite sheet, we don't want it lingering around in memory
	deleteImage(tempKey);
}

BitmapImage ImageLibrary::SeekImage(std::string imageKey)
{
	std::map<std::string, BitmapImage>::iterator i = images.find(imageKey);
	if (i != images.end())
	{
		return i->second;
	}
	else
	{
		return BitmapImage(" ",0,0,nullptr); //returns an empty bitmap image struct if we fail to find it
	}
}

void ImageLibrary::CopyImageReplaceColor(std::string imageKey, std::string newImageKey, Color colorToReplace, Color replaceWithColor)
{
	BitmapImage imageInfo = SeekImage(imageKey);
	if (! imageInfo.IsValid()) {
		return;
	}
	int t = imageInfo.width * imageInfo.height;
	BitmapImage newImageInfo(newImageKey, imageInfo.width, imageInfo.height, new Color[t]);
	for (int i = 0; i < t; i++)
	{
		if (imageInfo.pPixels[i] != colorToReplace)
		{
			newImageInfo.pPixels[i] = imageInfo.pPixels[i];
		}
		else
		{
			newImageInfo.pPixels[i] = replaceWithColor;
		}
	}
	loadImageIntoMap(newImageInfo);
}

void ImageLibrary::loadImageIntoMap(BitmapImage imageInfo)
{
	images.insert(std::pair<std::string, BitmapImage>(imageInfo.key, imageInfo));
}

void ImageLibrary::deleteImage(std::string imageKey)
{
	BitmapImage img = SeekImage(imageKey);
	//if the image has data, e.g it's got a valid pointer, delete the image info to ensure no memory leaks.
	if (img.IsValid())
	{
		//stored on the heap, must manually free the memory the pointer is holding or it'll just leak
		delete[] img.pPixels;
		img.pPixels = nullptr;
	}
	//delete BitmapImage from images map
	images.erase(imageKey);
}


