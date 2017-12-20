#include "Font.h"



Font::Font(BitmapImage fontImage) : image(fontImage)
{
}


Font::~Font()
{
}

//This is being abandoned, we'll tie into the imagelib stuff eventually
Surface Font::StrToSurface(std::string s, Color c)
{
	//Alright first things first, we need to figure out the dimensions of the string.  We know
	//each character is 32x32, but we need to know how big the entire string is
	int x = 0;
	int maxX = 0;
	int y = 0;
	//lets loop though the string and see what we've got
	for (char tmpC : s)
	{
		if (tmpC == '\n') {
			y += imageWH;
			x = 0; //reset x position
		}
		else
		{
			x += imageWH;
		}
		if (x > maxX) {
			maxX = x; //need to know our furthis X position
		}
	}
	//okay so this guys dimensions will be maxX by y
	Surface textSurface(maxX, y);
	//okay so lets go through the characters again, this time we'll figure out what bytes go where
	int writeX = 0;
	int writeY = 0;
	int linePosition = 0;
	int yOffset = 0;
	for (char letter : s)
	{
		if (letter == '\n')
		{
			linePosition = 0;
			yOffset += 1;
			continue;
		}
		//calculate the letters coords on it's parent image
		int letterIndex = letter - firstChar;
		int letterY = letterIndex / columns;
		int letterX = letterIndex % columns;
		//calculate where the character is in the font image
		int imagePositionX = imageWH * linePosition;
		int imagePositionY = yOffset;
		for (int y = 0; y < imageWH; y++)
		{
			for (x = 0; x < imageWH; x++)
			{
				//get the font's pixel to match the surface pixel
				//(yStart * width) + x
				int tmpIdx = ((letterY * image.width) + (x + (letterX * imageWH))); //debug so I can see what the value is
				//For the letter D I expect it to start at 1148
				Color pixC = image.pPixels[tmpIdx];
				if (pixC != Colors::Magenta) {
					textSurface.PutPixel(x + imagePositionX, y + imagePositionY, c);
				}
			}
		}

	}
	return textSurface;
}
