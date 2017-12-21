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