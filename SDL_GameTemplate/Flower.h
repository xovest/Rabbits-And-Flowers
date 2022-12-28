#pragma once
#include "Object.h"

class Flower : public Object {
protected:
	SDL_Texture* texture;
public:
	virtual void init(Game* _game, ResourceManager* _rm, int _id, float spawnX, float spawnY) = 0;
	void update(float deltaTime = 0.0f);
	void render();
	void spawn(bool noRespawn = false);
};