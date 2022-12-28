#pragma once
#include <sstream> 
#include "Game.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Timer.h"
using namespace std;

constexpr auto LEVEL_WIDTH = 50;
constexpr auto LEVEL_HEIGHT = 38;
constexpr auto TILE_SIZE = 16;

class Level {
private:
	SDL_Texture* map;
	Font* font;
	Game* game;
	ResourceManager* rm;
	Timer* timer;

	string P1text;
	string P2text;
	string textTime;
	string lifeLeft;

	stringstream gameplayTime;
public:
	Level(Game* _game, ResourceManager* _rm, Timer* _timer);
	~Level();

	void init();
	void render();
};