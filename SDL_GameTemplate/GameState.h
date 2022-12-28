#pragma once
#include <SDL.h>
#include "Game.h"
#include "Object.h"
#include "Player.h"
#include "Stats.h"

class GameState {
protected:
	Game* game;
public:
	virtual bool Init(Game* _game) = 0;
	virtual void HandleEvents(SDL_Event* event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Quit() = 0;
	virtual bool isColliding(Object* thisObject, Object* other) { return false; };
	virtual Player* getPlayer(int playerIndex) = 0;
	virtual void setEndMode(int _winner, EndMode _endMode) = 0;
};