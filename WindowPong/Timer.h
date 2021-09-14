#pragma once

#include <chrono>

using namespace std::chrono;

class Timer
{
public:
	Timer();
	~Timer();

	float getDeltaTime(); // time in nano seconds
private:
	high_resolution_clock::time_point currentTime;
	high_resolution_clock::time_point previousTime;
};

