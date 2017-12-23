#include "Animation.h"



Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::AddFrame(BitmapImage & image)
{
	frames.emplace_back(image);
}

void Animation::AdvanceFrame()
{
	if (++currentFrame >= frames.size())
	{
		currentFrame = 0;
	}
}

void Animation::Update(float deltaTime)
{
	//if we have more than 1 Frame we check for advancement of that frame.
	if (frames.size() > 1) {
		currentFrameTime += deltaTime;
		if (currentFrameTime >= frameHoldTime)
		{
			AdvanceFrame();
			currentFrameTime -= frameHoldTime; //remove our time leaving for time disparity in there
		}
	}
}

BitmapImage Animation::GetFrameImage()
{
	return frames[currentFrame];
}
