#pragma once
#include "Configuration.h"
#include "Object.h"
#include "Font.h"
#include "Timer.h"
using namespace std;

class Player : public Object {
private:
	SDL_Texture* sheet;

	int playerIndex;

	unsigned int score;

	float moveSpeed;
	
	float sheetRow;
	float sheetCol;
	float animSpeed;

	float dirX, dirY;

	bool mad;
	float poisonTime;
	float startPoisonTime;
	int timeLeft;

	float invertedContorlsTime;
	
	Timer timer;

	Font* font;

	void setColor();
	bool playersCollision(int id);
public:
	~Player();

	void init(Game* _game, ResourceManager* _rm, int _id, float spawnX = 400.0f, float spawnY = 300.0f);
	void update(float deltaTime);
	void render();

	void move(int dX, int dY);
	void setScore(unsigned int _score);
	void setMadMode(bool value);
	void incrementSpeed();
	void decrementSpeed(float minusSpeed, float scale = 1.0f);
	void increasePoisonTime(float plusTime);
	void setInvertedControls(float time);

	unsigned int getScore();
	float getSpeed();
	bool isMad();
};