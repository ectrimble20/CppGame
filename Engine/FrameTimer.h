#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float TimeMark();
private:
	std::chrono::steady_clock::time_point lastTimeMark;
};