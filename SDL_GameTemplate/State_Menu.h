#pragma once
#include "Object.h"
#include "State_Gameplay.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Player.h"
using namespace std;

class State_Menu : public GameState {
private:
	ResourceManager* rm;

	Font* font;
	float blinking;
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