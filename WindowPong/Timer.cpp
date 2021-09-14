#include "Timer.h"

Timer::Timer()
{
	currentTime = high_resolution_clock::now();
	previousTime = currentTime;
}

Timer::~Timer()
{
	
}

float Timer::getDeltaTime()
{
	previousTime = currentTime;
	currentTime = high_resolution_clock::now();

	nanoseconds deltaTime = duration_cast<nanoseconds>(currentTime - previousTime);
	return deltaTime.count();
}
