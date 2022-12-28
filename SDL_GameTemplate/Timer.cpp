#include "Timer.h"

Timer::Timer() {
	startTime = SDL_GetTicks();
}

float Timer::getTime() {
	return (float)(SDL_GetTicks() - startTime);
}
