#pragma once
#include "ImageLibrary.h"
#include "Surface.h"
#include <string>
#include "Colors.h"

class Font
{
public:
	Font() = delete; //must have an ImageLibrary reference
	Font(ImageLibrary & imgLibRef, const Color & alpha, const Color & textColor){
		imageLb = &imgLibRef;
		this->alpha = alpha;
		this->textColor = textColor;
	};
	~Font();
	Surface GetTextSurface(std::string text, std::string fontKey, int glyphWidth, int glyphHeight);
private:
	//these should be fixed sizes with the font image
	static constexpr char firstChar = ' '; //ASCII 32
	static constexpr char lastChar = '~'; //ASCII 126
	ImageLibrary * imageLb;
	Color alpha;
	Color textColor;
};

