#include "FrameTimer.h"

FrameTimer::FrameTimer()
{
	lastTimeMark = std::chrono::steady_clock::now();
}

float FrameTimer::TimeMark()
{
	const auto previousTimeMark = lastTimeMark;
	lastTimeMark = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = lastTimeMark - previousTimeMark;
	return frameTime.count();
}
