#pragma once
#include <vector>
#include "ImageLibrary.h" //humm, might need to move structs into their own world so we don't have import conflicts
class Animation
{
public:
	friend class Sprite;  //sprite can access us directly, we'll need this for Update()
	Animation();
	~Animation();
	void AddFrame(BitmapImage & image);
private:
	std::vector<BitmapImage> frames;
	float frameHoldTime = 0.0f; //this is set on creation and controls how long the frame is displayed.
	unsigned int currentFrame = 0;
	float currentFrameTime = 0.0f;
	void AdvanceFrame();
	void Update(float deltaTime);
	BitmapImage GetFrameImage();
};

