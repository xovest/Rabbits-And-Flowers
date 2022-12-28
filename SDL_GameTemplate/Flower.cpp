#include "Flower.h"
#include "Random.h"
#include "ResourceManager.h"

void Flower::render() {
	SDL_RenderCopy(game->getRenderer(), texture, NULL, &destRect);
}

void Flower::update(float deltaTime) {
	destRect.x = (int)x;
	destRect.y = (int)y;
}

void Flower::spawn(bool noRespawn) {
	if (noRespawn) {
		x = game->getWidth() - 30.0f;
		y = game->getWidth() - 30.0f;
	} else {
		x = Random::randNumber(border_x1 + 4.0f, border_x2 - sizeX - 4.0f);
		y = Random::randNumber(border_y1 + 4.0f, border_y2 - sizeY - 4.0f);
	}
}
