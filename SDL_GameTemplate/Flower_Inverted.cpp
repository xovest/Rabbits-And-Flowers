#include "Flower_Inverted.h"

void Flower_Inverted::init(Game* _game, ResourceManager* _rm, int _id, float spawnX, float spawnY) {
	game = _game;
	rm = _rm;

	border_x1 = CFG::GAME_BORDER_X1;
	border_x2 = CFG::GAME_BORDER_X2;
	border_y1 = CFG::GAME_BORDER_Y1;
	border_y2 = CFG::GAME_BORDER_Y2;

	sizeX = CFG::FLOWER02_SIZE_X;
	sizeY = CFG::FLOWER02_SIZE_Y;

	spawn();

	destRect.x = (int)x;
	destRect.y = (int)y;
	destRect.w = (int)sizeX;
	destRect.h = (int)sizeY;

	texture = rm->getTexture("assets/flower04.png");
}