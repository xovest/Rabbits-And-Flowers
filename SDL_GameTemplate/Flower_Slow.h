#pragma once
#include "Flower.h"

class Flower_Slow : public Flower {
public:
	void init(Game* _game, ResourceManager* _rm, int _id = 0, float spawnX = 0, float spawnY = 0);
};