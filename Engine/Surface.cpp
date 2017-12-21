#include "Surface.h"

Surface::Surface(int width, int height)
	: width(width), height(height), pPixels( new Color[width * height])
{
}

//Deep copy
Surface::Surface(const Surface & rhs)
	: Surface( rhs.GetWidth(), rhs.GetHeight())
{
	//once we have the constructor called with width and height, we can then copy the pixels over
	const int numberOfPixels = width * height;
	//loop through and assign each pixel
	for (int i = 0; i < numberOfPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Surface & Surface::operator=(const Surface & rhs)
{
	//get dimensions to copy
	width = rhs.GetWidth();
	height = rhs.GetHeight();
	//calculate number of pixels
	const int numberOfPixels = width * height;
	//free pixel buffer (ptr)
	delete[] pPixels;
	//reallocate a new buffer (ptr)
	pPixels = new Color[numberOfPixels];
	//loop through and assign each pixel
	for (int i = 0; i < numberOfPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
	//return reference to self
	return *this;
}

//Creates a surface using a .bmp (bitmap) file
Surface::Surface(const std::string & bitmapFilename)
{
	std::ifstream bitmapFile(bitmapFilename, std::ios::binary);
	BITMAPFILEHEADER bitmapFileHeader;
	bitmapFile.read(reinterpret_cast<char*>(&bitmapFileHeader), sizeof(bitmapFileHeader));

	BITMAPINFOHEADER bitmapInfoHeader;
	bitmapFile.read(reinterpret_cast<char*>(&bitmapInfoHeader), sizeof(bitmapInfoHeader));

	bool rowOrderRevered = false;
	bool is32Bit = bitmapInfoHeader.biBitCount == 32;
	width = bitmapInfoHeader.biWidth;
	height = bitmapInfoHeader.biHeight;
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

	pPixels = new Color[width * height];

	bitmapFile.seekg(bitmapFileHeader.bfOffBits);
	const int bitmapPadding = (4 - (width * 3) % 4) % 4;

	//untested
	for (yStart; yStart != yEnd; yStart += deltaY)
	{
		for (int x = 0; x < width; x++)
		{
			PutPixel(x, yStart, Color(bitmapFile.get(), bitmapFile.get(), bitmapFile.get()));
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
}

//This is changing to use the BitmapImage struct from ImageLibrary
Surface::Surface(BitmapImage imageData)
{
	width = imageData.width;
	height = imageData.height;
	pPixels = imageData.pPixels;
	//we set this flag because this means another class loaded the imageData and still has a reference to that pointer which
	//means it could be in use elseware.  As such, this class is NOT responsible for deleting the raw image memory data.
	//Whatever class originally loaded the data is.
	autoDeleteImagePointerData = false;
}


Surface::~Surface()
{
	//delete image data if it was loaded by the surface
	if (autoDeleteImagePointerData) {
		delete[] pPixels;
	}
	//point to nullptr
	pPixels = nullptr;
}

void Surface::PutPixel(int x, int y, Color c)
{
	pPixels[(y * width) + x] = c;
}

void Surface::PutPixel(int index, Color c)
{
	pPixels[index] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	return pPixels[(y * width) + x];
}

Color Surface::GetPixel(int index) const
{
	return pPixels[index];
}