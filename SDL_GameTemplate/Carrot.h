#pragma once
#include "Object.h"

class Carrot : public Object {
private:
	SDL_Texture* texture;
	float carrotFrame;
public:
	void init(Game* _game, ResourceManager* _rm, int _id = 0, float spawnX = 0, float spawnY = 0);
	void update(float deltaTime);
	void render();
	void relocate();
};