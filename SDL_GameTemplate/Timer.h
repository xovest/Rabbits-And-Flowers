#pragma once
#include <SDL.h>

class Timer {
public:
	Timer();
	float getTime();
private:
	Uint32 startTime;
};
