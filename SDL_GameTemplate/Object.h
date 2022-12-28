#pragma once
#include "Game.h"
#include "ResourceManager.h"

class Object {
protected:
	int id;

	float x, y;

	float sizeX, sizeY;

	float border_x1, border_x2;
	float border_y1, border_y2;

	SDL_Rect destRect, srcRect;

	Game* game;
	ResourceManager* rm;
public:
	virtual void init(Game* _game, ResourceManager* _rm, int _id, float spawnX, float spawnY) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

	bool collideWith(Object* other); // collide function
};