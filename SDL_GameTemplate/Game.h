#pragma once
#include <SDL.h>
#include <vector>
#include "Configuration.h"
#include "Stats.h"
#include "Window.h"
#include <fstream>
using namespace std;

class GameState;

class Game {
private:
	Window window;

	SDL_Event event;

	vector<GameState*> states;

	int newTime, oldTime;

	Stats* stats;

	bool _quit;

	void update();
	void render();
	void quit();
public:
	Game();
	
	bool init(GameState*);
	void thread();

	void pushState(GameState*);
	void popState();

	void setQuit();
	SDL_Renderer* getRenderer();

	int getWidth();
	int getHeight();

	GameState* getState();

	Stats* getStats();
};