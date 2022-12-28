#include "Game.h"
#include "GameState.h"

#include <iostream>

Game::Game() {
	oldTime = 0;
	newTime = 0;

	_quit = false;
}

bool Game::init(GameState* state) {
	window.init();
	stats = new Stats();

	ifstream load("game_save.txt");
	if (load) {
		unsigned int offset;
		string level;

		load >> offset;
		getStats()->SetP1Victories(offset);

		load >> offset;
		getStats()->SetP2Victories(offset);

		load.close();
	}

	if (getStats()->GetP1Victories() == 3 || getStats()->GetP2Victories() == 3) {
		getStats()->SetP1Victories(0);
		getStats()->SetP2Victories(0); 
	}

	stats->SetStateGameplayEnd(EndMode::NOT_STARTED);

	pushState(state);

	return true;
}

void Game::thread() {
	while (false == _quit) {
		update();
		render();
	}
	quit();
}

void Game::pushState(GameState* state) {
	states.push_back(state);

	if (states.back()->Init(this) == false) {
		_quit = true;
	}
}
void Game::popState() {
	states.back()->Quit();
	delete states.back();
	states.pop_back();

	if (states.size() == 0) {
		_quit = true;
	}
}
void Game::setQuit() {
	_quit = true;
}

SDL_Renderer* Game::getRenderer() {
	return window.getRenderer();
}

void Game::update() {
	while (SDL_PollEvent(&event)) {
		if (states.size() > 0) {
			states.back()->HandleEvents(&event);
		}
	}

	if (states.size() > 0) {
		oldTime = newTime;
		newTime = SDL_GetTicks();

		if (newTime > oldTime) {
			float deltaTime = (float)(newTime - oldTime) / 1000.0f;
			states.back()->Update(deltaTime);
		}
	}
}

void Game::render() {
	SDL_RenderClear(window.getRenderer());

	if (states.size() > 0)
		states.back()->Render();

	SDL_RenderPresent(window.getRenderer());
}
void Game::quit() {
	while (states.size() > 0) {
		popState();
	}

	ofstream save("game_save.txt");
	save << getStats()->GetP1Victories() << " " << getStats()->GetP2Victories();
	save.close();
	
	delete stats;
	stats = NULL;

	window.quit();
	SDL_Quit();
}

int Game::getWidth() {
	return window.getWidth();
}

int Game::getHeight() {
	return window.getHeight();
}

GameState* Game::getState() {
	return states.back();
}

Stats* Game::getStats() {
	return stats;
}