#include "State_End.h"
#include <sstream>
#include <ios>

using CFG::PLAYER_1;
using CFG::PLAYER_FONT_2;
using CFG::BLACK_COLOR;

bool State_End::Init(Game* _game) {
	game = _game;
	rm = new ResourceManager(game);

	try {
		rm->loadTexture("assets/font_texture.png");
	}
	catch (runtime_error &e) {
		cerr << e.what() << endl;
		return false;
	}

	font = new Font(game, rm->getTexture("assets/font_texture.png"), 16, 16, 8, 16);

	P1_score = game->getStats()->GetP1Score();
	P2_score = game->getStats()->GetP2Score();
	P1_victories = game->getStats()->GetP1Victories();
	P2_victories = game->getStats()->GetP2Victories();
	gameplayTime = game->getStats()->GetGameplayTime();
	stateGameplayEnd = game->getStats()->GetStateGameplayEnd();

	return true;
}

void State_End::HandleEvents(SDL_Event* event) {
	if (event->type == SDL_QUIT)
		game->setQuit();
	else if (event->type == SDL_KEYDOWN) {
		if (event->key.keysym.sym == SDLK_ESCAPE)
			if (P1_victories == 3 || P2_victories == 3)
				game->setQuit();
			else
				game->popState();

		if (event->key.keysym.sym == SDLK_RETURN)
			if (P1_victories == 3 || P2_victories == 3)
				game->setQuit();
			else
				game->popState();
	}
}

void State_End::Update(float deltaTime) {
	if (P1_victories > P2_victories)
		SDL_SetRenderDrawColor(game->getRenderer(), PLAYER_1.r, PLAYER_1.g, PLAYER_1.b, PLAYER_1.a);
	else if (P2_victories > P1_victories)
		SDL_SetRenderDrawColor(game->getRenderer(), PLAYER_FONT_2.r, PLAYER_FONT_2.g, PLAYER_FONT_2.b, PLAYER_FONT_2.a);
	else
		SDL_SetRenderDrawColor(game->getRenderer(), BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a);
}

void State_End::Render() {
	stringstream text("");
	streamsize x;

	if (P1_victories == 3) {
		text.str("     PLAYER 1 WON!");
		x = text.str().length() * 8 / 2;
		font->renderString(game->getWidth() / 3 - 3 * (int)x, game->getHeight() / 5, text.str(), 4);
		text.str("");

		text.str("PRESS ENTER/ESC TO QUIT");
		x = text.str().length() * 8 / 2;
		font->renderString(game->getWidth() / 2 - 3 * (int)x, game->getHeight() / 3, text.str(), 3);
		text.str("");
	}
	else if (P2_victories == 3) {
		text.str("     PLAYER 2 WON!");
		x = text.str().length() * 8 / 2;
		font->renderString(game->getWidth() / 3 - 3 * (int)x, game->getHeight() / 5, text.str(), 4);
		text.str("");

		text.str("PRESS ENTER/ESC TO QUIT");
		x = text.str().length() * 8 / 2;
		font->renderString(game->getWidth() / 2 - 3 * (int)x, game->getHeight() / 3, text.str(), 3);
		text.str("");
	}
	else {
		text.str("PRESS ENTER/ESC FOR MAIN MENU");
		x = text.str().length() * 8 / 2;
		font->renderString(game->getWidth() / 2 - 3 * (int)x, game->getHeight() / 3, text.str(), 3);
		text.str("");
	}

	text << "P1 VICTORIES: " << P1_victories;
	x = text.str().length() * 8 / 2;
	font->renderString(game->getWidth() / 4 - 2 * (int)x, game->getHeight() / 2, text.str(), 2);
	text.str("");

	text << "P2 VICTORIES: " << P2_victories;
	x = text.str().length() * 8 / 2;
	font->renderString(game->getWidth() / 4 * 3 - 2 * (int)x, game->getHeight() / 2, text.str(), 2);
	text.str("");
}

void State_End::Quit() {
	delete font;
	font = NULL;
	delete rm;
	rm = NULL;
}

bool State_End::isColliding(Object* thisObject, Object* other) {
	return false;
}

Player* State_End::getPlayer(int playerIndex) {
	return NULL;
}

void State_End::setEndMode(int _winner, EndMode _endMode) {}