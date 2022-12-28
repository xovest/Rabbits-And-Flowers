#pragma once
#include <vector>
#include "Configuration.h"
#include "GameState.h"
#include "State_End.h"
#include "Stats.h"
#include "ResourceManager.h"
#include "Level.h"
#include "Font.h"
#include "Timer.h"
#include "Player.h"
#include "Carrot.h"
#include "Flower_Dead.h"
#include "Flower_Slow.h"
#include "Flower_Mad.h"
#include "Flower_Inverted.h"
#include "Flower_Speed.h"
using namespace std;

class State_Gameplay : public GameState {
private:
	ResourceManager* rm;

	vector<Carrot*> carrots;
	vector<Flower_Dead*> flowers_dead;
	vector<Flower_Slow*> flowers_slow;
	vector<Flower_Mad*> flowers_mad;
	vector<Flower_Inverted*> flowers_inverted;
	vector<Flower_Speed*> flowers_speed;

	Player Player1;
	Player Player2;
	int winner;
	EndMode endMode;

	Level* level;
	Font* font;
	Timer* timer;

	void theEnd();
public:
	bool Init(Game* _game);
	void HandleEvents(SDL_Event* event);
	void Update(float deltaTime);
	void Render();
	void Quit();

	bool isColliding(Object* thisObject, Object* other); // collision

	Player* getPlayer(int playerIndex);

	void setEndMode(int _winner, EndMode _endMode);

	bool collideWithOtherObjects(Object* object);
};