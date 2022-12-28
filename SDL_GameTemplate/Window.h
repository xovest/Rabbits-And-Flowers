#pragma once
#include <SDL.h>
#include "Configuration.h"
#include <iostream>
using namespace std;

class Window {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	int screenWidth;
	int screenHeight;
public:
	Window();
	bool init();
	void quit();
	int getWidth();
	int getHeight();
	SDL_Renderer* getRenderer();
};