#include "Carrot.h"
#include "Random.h"

void Carrot::init(Game* _game, ResourceManager* _rm, int _id, float spawnX, float spawnY) {
	game = _game;
	rm = _rm;

	border_x1 = CFG::GAME_BORDER_X1;
	border_x2 = CFG::GAME_BORDER_X2;
	border_y1 = CFG::GAME_BORDER_Y1;
	border_y2 = CFG::GAME_BORDER_Y2;
	
	sizeX = 20;
	sizeY = 20;

	carrotFrame = 0.0f;
	relocate();

	texture = rm->getTexture("assets/carrot.png");
}

void Carrot::update(float deltaTime) {
	carrotFrame += (deltaTime + Random::randNumber(10, 500) / 10000.0f) / 8;

	if (carrotFrame >= 2.0f)
		carrotFrame = 0.0f;

	destRect.x = (int)x;
	destRect.y = (int)y;
	destRect.w = (int)sizeX;
	destRect.h = (int)sizeY;

	srcRect.x = 0;
	srcRect.y = (int)carrotFrame * (int)sizeY;
	srcRect.w = (int)sizeX;
	srcRect.h = (int)sizeY;
}

void Carrot::render() {
	SDL_RenderCopy(game->getRenderer(), texture, &srcRect, &destRect);
}

void Carrot::relocate() {
	x = Random::randNumber(border_x1 + 4.0f, border_x2 - sizeX - 4.0f); // +-4 for preventing spawning next to the border
	y = Random::randNumber(border_y1 + 4.0f, border_y2 - sizeY - 4.0f);

	carrotFrame = (float)Random::randNumber(0, 1);
}