#pragma once
#include "GameState.h"
#include "Configuration.h"
#include "Stats.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Player.h"
#include <string>
#include <fstream>

using namespace std;

class State_End : public GameState {
private:
	ResourceManager* rm;

	Font* font;

	unsigned int P1_score;
	unsigned int P2_score;

	unsigned int P1_victories;
	unsigned int P2_victories;

	float gameplayTime;
	EndMode stateGameplayEnd;
public:
	bool Init(Game* _game);
	void HandleEvents(SDL_Event* event);
	void Update(float deltaTime);
	void Render();
	void Quit();
	bool isColliding(Object* thisObject, Object* other);
	Player* getPlayer(int playerIndex);
	void setEndMode(int _winner, EndMode _endMode);
};