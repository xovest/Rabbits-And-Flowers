#include "ResourceManager.h"
#include "Game.h"

ResourceManager::ResourceManager(Game* _game) {
	game = _game;
}

ResourceManager::~ResourceManager() {
	auto i = textures.begin();
	while (i != textures.end()) {
		SDL_DestroyTexture(i->second);
		i++;
	}
	textures.clear();
}

void ResourceManager::loadTexture(const string filePath) {
	SDL_Texture* newTexture = NULL;
	newTexture = IMG_LoadTexture(game->getRenderer(), filePath.c_str());

	if (NULL == newTexture) {
		throw runtime_error("Error while loading texture " + filePath);
	}

	textures.insert(pair<string, SDL_Texture*>(filePath, newTexture));
}

SDL_Texture* ResourceManager::getTexture(const string filePath) {
	SDL_Texture* texture = NULL;
	auto i = textures.find(filePath);

	texture = i->second;

	return texture;
}