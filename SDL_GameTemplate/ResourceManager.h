#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Game;

class ResourceManager {
private:
	Game* game;
	map<string, SDL_Texture*> textures;
public:
	ResourceManager(Game* _game);
	~ResourceManager();
	void loadTexture(const string filePath);
	SDL_Texture* getTexture(const string filePath);
};