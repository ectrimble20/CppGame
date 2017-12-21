#pragma once
#include "ImageLibrary.h"
#include "Surface.h"
#include <string>
#include "Colors.h"

class Font
{
public:
	Font() = delete; //must have an ImageLibrary reference
	Font(ImageLibrary & imgLibRef){
		imageLb = &imgLibRef;
	};
	~Font();
	Surface GetTextSurface(std::string text, std::string fontKey, int glyphSize);
private:
	//these should be fixed sizes with the font image
	static constexpr char firstChar = ' '; //ASCII 32
	static constexpr char lastChar = '~'; //ASCII 126
	ImageLibrary * imageLb;
};

