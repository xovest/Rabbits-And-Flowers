#include "Player.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "GameState.h"

Player::~Player() {
	delete font;
	font = NULL;
}

void Player::init(Game* _game, ResourceManager* _rm, int _id, float spawnX, float spawnY) {
	game = _game;
	rm = _rm;
	id = _id;

	border_x1 = CFG::GAME_BORDER_X1;
	border_x2 = CFG::GAME_BORDER_X2;
	border_y1 = CFG::GAME_BORDER_Y1;
	border_y2 = CFG::GAME_BORDER_Y2;

	font = new Font(game, rm->getTexture("assets/font_texture.png"), 16, 16, 8, 16);

	sizeX = CFG::PLAYER_SIZE_X;
	sizeY = CFG::PLAYER_SIZE_Y;

	x = spawnX;
	y = spawnY;

	sheetRow = 0.0f;
	sheetCol = 0.0f;
	animSpeed = 12.0f;
	sheet = rm->getTexture("assets/bunnies.png");
	setColor();

	moveSpeed = CFG::START_SPEED;

	dirX = 0.0f;
	dirY = 0.0f;

	invertedContorlsTime = 0;

	poisonTime = CFG::POISON_TIME;
	mad = false;
	score = 0;
}

void Player::update(float deltaTime) {
	if (invertedContorlsTime > timer.getTime()) {
		dirX *= -1;
		dirY *= -1;
	}

	if (dirX != 0.0f || dirY != 0.0f) {
		sheetRow += animSpeed * deltaTime;
		if (sheetRow >= 4) {
			sheetRow = 0.0f;
		}
	} else {
		sheetRow = 0.0f;
	}

	if (dirX > 0)
		sheetCol = 3;
	if (dirX < 0)
		sheetCol = 2;
	if (dirY > 0)
		sheetCol = 0;
	if (dirY < 0)
		sheetCol = 1;

	x += dirX * deltaTime * moveSpeed;
	y += dirY * deltaTime * moveSpeed;
	
	if (playersCollision(id)) {
		if (isMad()) 
			game->getState()->setEndMode(id, EndMode::GOT_EATEN_MODE);
		else {
			x -= dirX * deltaTime * moveSpeed;
			y -= dirY * deltaTime * moveSpeed;
		}
	}

	if (x > border_x2 - sizeX)
		x = border_x2 - sizeX;
	if (x < border_x1)
		x = border_x1;
	if (y > border_y2 - sizeY)
		y = border_y2 - sizeY;
	if (y < border_y1)
		y = border_y1;

	srcRect.x = (int)sizeX * (int)sheetCol;
	srcRect.y = (int)sizeY * (int)sheetRow;
	srcRect.w = (int)sizeX;
	srcRect.h = (int)sizeY;

	destRect.x = (int)x;
	destRect.y = (int)y;
	destRect.w = (int)sizeX;
	destRect.h = (int)sizeY;

	dirX = 0.0f;
	dirY = 0.0f;

	if (isMad()) { // the mad case
		if ((int)poisonTime < (int)timer.getTime() - (int)startPoisonTime) {
			if (id == 1)
				game->getState()->setEndMode(2, EndMode::POISONED_MODE);
			else
				game->getState()->setEndMode(1, EndMode::POISONED_MODE);
		}
	}
}

void Player::render() {
	setColor();	
	font->renderChar((int)(x + sizeX / 2 - 4), (int)(y - sizeY / 4 - 8), id + '0');

	if (isMad()) { // mad time
		timeLeft = (int)poisonTime - ((int)timer.getTime() - (int)startPoisonTime);

		font->setColor(CFG::BLACK_COLOR.r, CFG::BLACK_COLOR.g, CFG::BLACK_COLOR.b);
		stringstream _timeLeft;
		_timeLeft << setw(3) << setfill(' ') << timeLeft / 1000 << "."
			<< setw(2) << setfill('0') << (timeLeft % 1000) / 10;
		font->renderString((game->getWidth() - 50) - 137, 5, _timeLeft.str());

		_timeLeft.str(string());
	}

	SDL_RenderCopy(game->getRenderer(), sheet, &srcRect, &destRect);
}

void Player::move(int dX, int dY) {
	if (dX && dY) {
		dirX += (float)dX / 1.41421356237f;
		dirY += (float)dY / 1.41421356237f;
	} else {
		dirX += (float)dX;
		dirY += (float)dY;
	}
}

void Player::setScore(unsigned int _score) {
	if (score == -1)
		score = 0;
	else
		score += _score;
}

void Player::setMadMode(bool value) {
	startPoisonTime = timer.getTime();
	mad = value;
}

void Player::incrementSpeed() {
	if (moveSpeed >= CFG::START_SPEED * 8) {
		moveSpeed += CFG::SPEED_INCREASE / 8;
	} else if (moveSpeed >= CFG::START_SPEED * 4) {
		moveSpeed += CFG::SPEED_INCREASE / 4;
	} else if (moveSpeed >= CFG::START_SPEED * 2) {
		moveSpeed += CFG::SPEED_INCREASE / 2;
	} else {
		moveSpeed += CFG::SPEED_INCREASE / 1;
	}
}

void Player::decrementSpeed(float minusSpeed, float scale) {
	if (moveSpeed < 32.0f) {
		moveSpeed -= minusSpeed * scale / 4.0f;
	} else if (moveSpeed < 48.0f) {
		moveSpeed -= minusSpeed * scale / 2.0f;
	} else {
		moveSpeed -= minusSpeed * scale;
	}
}

void Player::increasePoisonTime(float plusTime) {
	startPoisonTime += plusTime;
}

void Player::setInvertedControls(float time) {
	invertedContorlsTime = timer.getTime() + time;
}

unsigned int Player::getScore() {
	return score;
}

float Player::getSpeed() {
	return moveSpeed;
}

bool Player::isMad() {
	return mad;
}

void Player::setColor() {
	if (id == 1) {
		SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r, CFG::PLAYER_1.g, CFG::PLAYER_1.b);
		font->setColor(CFG::PLAYER_FONT_1.r, CFG::PLAYER_FONT_1.g, CFG::PLAYER_FONT_1.b);
	} else if (id == 2) {
		SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r, CFG::PLAYER_2.g, CFG::PLAYER_2.b);
		font->setColor(CFG::PLAYER_FONT_2.r, CFG::PLAYER_FONT_2.g, CFG::PLAYER_FONT_2.b);
	} else {
		SDL_SetTextureColorMod(sheet, 0, 0, 0);
		font->resetColor();
	}

	if (isMad()) { // getting darker and darker when mad
		if (id == 2) {
			if (9 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r * 1 / 18, CFG::PLAYER_2.g * 1 / 18, CFG::PLAYER_2.b * 1 / 18);
			else if (8 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r * 3 / 18, CFG::PLAYER_2.g * 3 / 18, CFG::PLAYER_2.b * 3 / 18);
			else if (7 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r * 5 / 18, CFG::PLAYER_2.g * 5 / 18, CFG::PLAYER_2.b * 5 / 18);
			else if (6 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r * 7 / 18, CFG::PLAYER_2.g * 7 / 18, CFG::PLAYER_2.b * 7 / 18);
			else if (5 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r * 9 / 18, CFG::PLAYER_2.g * 9 / 18, CFG::PLAYER_2.b * 9 / 18);
			else if (4 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r * 11 / 18, CFG::PLAYER_2.g * 11 / 18, CFG::PLAYER_2.b * 11 / 18);
			else if (3 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r * 13 / 18, CFG::PLAYER_2.g * 13 / 18, CFG::PLAYER_2.b * 13 / 18);
			else if (2 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r * 14 / 18, CFG::PLAYER_2.g * 14 / 18, CFG::PLAYER_2.b * 14 / 18);
			else if (1 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r * 16 / 18, CFG::PLAYER_2.g * 16 / 18, CFG::PLAYER_2.b * 16 / 18);
			else
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_2.r * 17 / 18, CFG::PLAYER_2.g * 17 / 18, CFG::PLAYER_2.b * 17 / 18);
		} else {
			if (9 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r * 1 / 18, CFG::PLAYER_1.g * 1 / 18, CFG::PLAYER_1.b * 1 / 18);
			else if (8 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r * 3 / 18, CFG::PLAYER_1.g * 3 / 18, CFG::PLAYER_1.b * 3 / 18);
			else if (7 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r * 5 / 18, CFG::PLAYER_1.g * 5 / 18, CFG::PLAYER_1.b * 5 / 18);
			else if (6 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r * 7 / 18, CFG::PLAYER_1.g * 7 / 18, CFG::PLAYER_1.b * 7 / 18);
			else if (5 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r * 9 / 18, CFG::PLAYER_1.g * 9 / 18, CFG::PLAYER_1.b * 9 / 18);
			else if (4 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r * 11 / 18, CFG::PLAYER_1.g * 11 / 18, CFG::PLAYER_1.b * 11 / 18);
			else if (3 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r * 13 / 18, CFG::PLAYER_1.g * 13 / 18, CFG::PLAYER_1.b * 13 / 18);
			else if (2 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r * 14 / 18, CFG::PLAYER_1.g * 14 / 18, CFG::PLAYER_1.b * 14 / 18);
			else if (1 * (int)poisonTime / 10 < (int)timer.getTime() - (int)startPoisonTime)
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r * 16 / 18, CFG::PLAYER_1.g * 16 / 18, CFG::PLAYER_1.b * 16 / 18);
			else
				SDL_SetTextureColorMod(sheet, CFG::PLAYER_1.r * 17 / 18, CFG::PLAYER_1.g * 17 / 18, CFG::PLAYER_1.b * 17 / 18);
		}
	}
}

bool Player::playersCollision(int id) {
	Player* otherPlayer = game->getState()->getPlayer(id);
	if (game->getState()->isColliding(this, otherPlayer))
		return true;

	return false;
}