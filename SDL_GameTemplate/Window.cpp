#include "Window.h"

Window::Window() {
	window = NULL;
	renderer = NULL;
	screenWidth = CFG::SCREEN_WIDTH;
	screenHeight = CFG::SCREEN_HEIGHT;
}

bool Window::init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			cerr << SDL_GetError() << endl;
			return false;
		}

		window = SDL_CreateWindow("Rabbits And Flowers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (NULL == window) {
			cerr << SDL_GetError() << endl;
			return false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
		if (NULL == renderer) {
			cerr << SDL_GetError() << endl;
			return false;
		}

		SDL_ShowCursor(CFG::SHOW_CURSOR);
		SDL_SetRenderDrawColor(renderer, 0xAB, 0xD0, 0x3F, 0xFF);

		return true;
}

int Window::getWidth() {
	return screenWidth;
}

int Window::getHeight() {
	return screenHeight;
}

SDL_Renderer* Window::getRenderer() {
	return renderer;
}

void Window::quit() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}