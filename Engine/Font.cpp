#include "Font.h"

Font::~Font()
{
}

Surface Font::GetTextSurface(std::string text, std::string fontKey, int glyphWidth, int glyphHeight)
{
	//lets first figure out how large our string is so we can create a big enough array to hold everything
	int wIdx = 0;
	int width = 0;
	int height = glyphHeight;
	for (char c : text)
	{
		if (c == '\n')
		{
			//we need to note what our height is
			height += glyphHeight;
			wIdx = 0;
		}
		else
		{
			wIdx += 1;
			if ((wIdx * glyphWidth) > width)
			{
				width += glyphWidth;
			}
		}
	}
	//so here we should know our height + our maximum width, e.g how many characters are on our longest line.
	const unsigned int size = width * height;

	//lets make our new color array
	Color * pTextPixels = new Color[size];

	//okay, now to build our pixel array we need to know what index we're when considering the string as a 2D array
	//so for instance this sentence:
	//MY HOUSE IS MADE
	//OF LEAD AND COAL
	//
	//Is 16x2 in size, it contains 33 characters however because there's a \n between MADE and OF
	//but we can discard that.
	//if we consider that each letter is 32 characters, we can know the required indexes of the pixels in each letter
	//by considering the letters relative index in the sentence.
	//
	//so again, if we take the index of H in house, we know it's array index would be 3,0.
	//So we can immediately tell that it's top left X,Y is 32*3,32*0, so 96,0, which means it's pixel index will start
	//at 96 because the formula for getting the pixel index is (y*width) + x, which in this case is (0*(32*16)) + 96
	//this becomes more complicated as we work down the pixels of the letter, so we want to get the second line of pixels
	//for the letter, so we now move down Y by 1, but Y by the pixel index, not the letter index.
	//So the top left pixel index of the second row is now (1*(32*16)) + 96 or 609, which means we need the 609th pixel
	//of our sentence pixels (pTextPixels) to be the 129th pixel of the letter H (because the H itself is (1*32) + 96.

	//okay lets get started
	unsigned int sentenceIndexX = 0;
	unsigned int sentenceIndexY = 0;
	for (char c : text)
	{
		if (c == '\n')
		{
			sentenceIndexY += 1; //move to the next line
			sentenceIndexX = 0; //reset to the begining of the line
		}
		else if (c == ' ')
		{
			//move forward
			sentenceIndexX += 1;
		}
		else
		{
			//make sure this is a valid ANCII char
			if (c > firstChar && c <= lastChar)
			{
				int cIdx = c - ' '; //get the index of the character
				std::string lookupKey = fontKey + "_" + std::to_string(cIdx);
				BitmapImage letterImage = imageLb->SeekImage(lookupKey); //we'll want a check in here at some point but for now... nah
				//this is where we actually want to copy the image's pixels into our image
				int startX = sentenceIndexX * glyphWidth;
				int startY = sentenceIndexY * glyphHeight;
				int stopX = startX + glyphWidth;
				int stopY = startY + glyphHeight;
				int glyphX = 0;
				int glyphY = 0;
				for (int y = startY; y < stopY; y++)
				{
					for (int x = startX; x < stopX; x++)
					{
						int pixelIdx = (y*width) + x;
						int glyphIdx = (glyphY * glyphWidth) + glyphX;
						//if at any point our indexs get out of bounds I need to know
						//copy the pixel
						//handle color correcting here
						Color clr = letterImage.pPixels[glyphIdx];
						//we only care if it's not our alpha color or our text color
						if (clr != alpha && clr != textColor)
						{
							clr = textColor;
						}
						pTextPixels[pixelIdx] = clr;// letterImage.pPixels[glyphIdx];
						glyphX += 1;
					}
					glyphY += 1;
					glyphX = 0;
				}

			}
			sentenceIndexX += 1;
		}
	}
	//last thing to do is return a surface, I don't think we need to delete the pTextPixels because it's handed to the 
	//surface, so it should be deleted by the surface when it is deconstructed.

	//okay, got an exception when Surface tried to delete it, we'll try deleting here?
	//okay, this time I hand the pTextPixels to Surface, surface copies the pixels to it's own array
	//so we SHOULD be able to delete pTextPixels without breaking surface since it'll have it's own copy
	//which is how this should work because Surfaces should be reusable.
	Surface textSurf = Surface(width, height);
	//loop through the pixels and assign them to the surface
	for (unsigned int i = 0; i < size; i++)
	{
		textSurf.PutPixel(i, pTextPixels[i]);
	}
	delete[] pTextPixels;
	return textSurf;
}

