#pragma once
#include <SDL.h>

class Timer {
public:
	Timer();
	float getTime();
private:
	float startTime;
};