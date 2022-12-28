#include "Level.h"
#include <iomanip>

Level::Level(Game* _game, ResourceManager* _rm, Timer* _timer) {
	game = _game;
	rm = _rm;
	timer = _timer;
	map = NULL;
}

Level::~Level() {
	delete font;
	font = NULL;
	map = NULL;
}

void Level::init() {
	map = rm->getTexture("assets/map.png");
	SDL_SetTextureColorMod(map, CFG::MAP_COLOR.r, CFG::MAP_COLOR.g, CFG::MAP_COLOR.b);
	font = new Font(game, rm->getTexture("assets/font_texture.png"), 16, 16, 8, 16);

	P1text = "P1 > Score:    - Speed:";
	P2text = "P2 > Score:    - Speed:";
	textTime = "Time:";
	lifeLeft = "Life Left:";
}

void Level::render() {
	// map
	SDL_Rect screen = { 0, 0, game->getWidth(), game->getHeight() };
	SDL_RenderCopy(game->getRenderer(), map, NULL, &screen);

	// score and speed for player 1
	font->setColor(CFG::PLAYER_FONT_1.r, CFG::PLAYER_FONT_1.g, CFG::PLAYER_FONT_1.b);
	font->renderString(7, 5, P1text);

	// score and speed for player 2
	font->setColor(CFG::PLAYER_FONT_2.r, CFG::PLAYER_FONT_2.g, CFG::PLAYER_FONT_2.b);
	font->renderString((game->getWidth() / 2) + 7 - 135, 5, P2text);

	// time counter and life left
	font->setColor(CFG::BLACK_COLOR.r, CFG::BLACK_COLOR.g, CFG::BLACK_COLOR.b);
	font->renderString((game->getWidth() - 100 - 2), 5, textTime);
	font->renderString((game->getWidth() - 100) - 160, 5, lifeLeft);

	// format
	gameplayTime << setw(3) << setfill(' ') << (int)timer->getTime() / 1000 << "."
		<< setw(2) << setfill('0') << ((int)timer->getTime() % 1000) / 10;
	font->renderString((game->getWidth() - 100) + 40, 5, gameplayTime.str());

	gameplayTime.str(string());
}