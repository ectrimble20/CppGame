#include "ImageLibrary.h"


ImageLibrary::ImageLibrary()
{
	preload();
}

ImageLibrary::~ImageLibrary()
{
	//since we're storing everything via ptr's on the heap, we need to go through and destroy all the color arrays.
	std::map<std::string, BitmapImage>::iterator i;
	for (i = images.begin(); i != images.end(); i++)
	{
		if (i->second.pPixels != nullptr)
		{
			delete[] i->second.pPixels;
			i->second.pPixels = nullptr;
		}
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
	GameLogger::Log("Loaded image " + imageInfo.key);
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
	GameLogger::Log("Unloaded image " + imageKey);
}

void ImageLibrary::preload()
{
	ImportSingleImage("charcoal64", "Images/charcoal_64x64.bmp");
	ImportFontImages("Lucida","Images/Font_Lucida_26pt_32x32_32x3y.bmp",32,32,32,3);
	ImportFontImages("Luci_White", "Images/Lucida_white_320x48_10x16.bmp", 10, 16, 32, 3);
	ImportSingleImage("button_exit", "Images/button_exit_128x32.bmp");
	//I think we'll make a function specifically to load font's, we'll know their size, thier start and end points
	//and having them as individual images is no worse than having a single large image.

	//std::string key, int w, int h, int x, int y
	SpriteSheetCell * man1 = new SpriteSheetCell[12];
	man1[0] = SpriteSheetCell("man1_front_idle", 32, 32, 0, 0);
	man1[1] = SpriteSheetCell("man1_front_walk1", 32, 32, 32, 0);
	man1[2] = SpriteSheetCell("man1_front_walk2", 32, 32, 64, 0);
	man1[3] = SpriteSheetCell("man1_back_idle", 32, 32, 0, 32);
	man1[4] = SpriteSheetCell("man1_back_walk1", 32, 32, 32, 32);
	man1[5] = SpriteSheetCell("man1_back_walk2", 32, 32, 64, 32);
	man1[6] = SpriteSheetCell("man1_left_idle", 32, 32, 0, 64);
	man1[7] = SpriteSheetCell("man1_left_walk1", 32, 32, 32, 64);
	man1[8] = SpriteSheetCell("man1_left_walk2", 32, 32, 64, 64);
	man1[9] = SpriteSheetCell("man1_right_idle", 32, 32, 0, 96);
	man1[10] = SpriteSheetCell("man1_right_walk1", 32, 32, 32, 96);
	man1[11] = SpriteSheetCell("man1_right_walk2", 32, 32, 64, 96);
	ImportSpriteSheet("Images/man3_32x32_4dir_3frame_idle_and_walk_rdy.bmp", man1, 12);
	delete[] man1;

	SpriteSheetCell * man2 = new SpriteSheetCell[12];
	man2[0] = SpriteSheetCell("man2_front_idle", 32, 32, 0, 0);
	man2[1] = SpriteSheetCell("man2_front_walk1", 32, 32, 32, 0);
	man2[2] = SpriteSheetCell("man2_front_walk2", 32, 32, 64, 0);
	man2[3] = SpriteSheetCell("man2_back_idle", 32, 32, 0, 32);
	man2[4] = SpriteSheetCell("man2_back_walk1", 32, 32, 32, 32);
	man2[5] = SpriteSheetCell("man2_back_walk2", 32, 32, 64, 32);
	man2[6] = SpriteSheetCell("man2_left_idle", 32, 32, 0, 64);
	man2[7] = SpriteSheetCell("man2_left_walk1", 32, 32, 32, 64);
	man2[8] = SpriteSheetCell("man2_left_walk2", 32, 32, 64, 64);
	man2[9] = SpriteSheetCell("man2_right_idle", 32, 32, 0, 96);
	man2[10] = SpriteSheetCell("man2_right_walk1", 32, 32, 32, 96);
	man2[11] = SpriteSheetCell("man2_right_walk2", 32, 32, 64, 96);
	ImportSpriteSheet("Images/man2_32x32_4dir_3frame_idle_and_walk_rdy.bmp", man2, 12);
	delete[] man2;


	SpriteSheetCell * man3 = new SpriteSheetCell[12];
	man3[0] = SpriteSheetCell("man_front_idle", 32, 32, 0, 0);
	man3[1] = SpriteSheetCell("man_front_walk1", 32, 32, 32, 0);
	man3[2] = SpriteSheetCell("man_front_walk2", 32, 32, 64, 0);
	man3[3] = SpriteSheetCell("man_back_idle", 32, 32, 0, 32);
	man3[4] = SpriteSheetCell("man_back_walk1", 32, 32, 32, 32);
	man3[5] = SpriteSheetCell("man_back_walk2", 32, 32, 64, 32);
	man3[6] = SpriteSheetCell("man_left_idle", 32, 32, 0, 64);
	man3[7] = SpriteSheetCell("man_left_walk1", 32, 32, 32, 64);
	man3[8] = SpriteSheetCell("man_left_walk2", 32, 32, 64, 64);
	man3[9] = SpriteSheetCell("man_right_idle", 32, 32, 0, 96);
	man3[10] = SpriteSheetCell("man_right_walk1", 32, 32, 32, 96);
	man3[11] = SpriteSheetCell("man_right_walk2", 32, 32, 64, 96);
	ImportSpriteSheet("Images/man_32x32_4dir_3frame_idle_and_walk_rdy.bmp", man3, 12);
	delete[] man3;
	GameLogger::Log("Preload images completed");
}

void ImageLibrary::ImportFontImages(std::string fontKey, std::string fontImage, int glyphWidth, int glyphHeight, int columns, int rows)
{
	//so we know our font's will be " " through ~ on the ANSII table which is 32 through 126.
	//We can minus 32 from each letter which gives us 0 - 94 (technically 0-95 but the 127 char is DEL and we don't show that).
	//each row will contain X columns and each image will have X rows, generally, with a normal ANSII table it's 32x3.
	//we'll leave it as variables in case we change it at some point.
	//To keep track of a key, we'll use "fontKey" + "_" + character code.  So for instance A, which is 65, will become
	//FONTNAME_30, because we will subtract 32 from 65 so our characters start at 0.
	//BitmapImage fontImage = SeekImage(fontKey); we don't need to do this, we can just build a SheetCell array and load it without the base image
	//unsigned int charRemove = 32; //so it's not hard coded into the code itself //unused
	int i = 0;
	int x = 0;
	int y = 0;
	SpriteSheetCell * fontCells = new SpriteSheetCell[columns * rows];
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			//unsigned char ch = i; //unused
			std::string cellName = fontKey + "_" + std::to_string(i);
			fontCells[i] = SpriteSheetCell(cellName, glyphWidth, glyphHeight, x, y);
			x += glyphWidth;
			i += 1; //should remember to increment the damn array
		}
		x = 0;
		y += glyphHeight;
	}
	ImportSpriteSheet(fontImage, fontCells, (columns * rows));
	delete[] fontCells; //clean up our heap array.
	GameLogger::Log("Font Image " + fontKey + " character images loaded");
}
