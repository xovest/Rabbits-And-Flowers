#include "State_Menu.h"

bool State_Menu::Init(Game* _game) {
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

	blinking = 0.0f;

	return true;
}

void State_Menu::HandleEvents(SDL_Event* event) {
	if (event->type == SDL_QUIT)
		game->setQuit();
	else if (event->type == SDL_KEYDOWN) {
		if (event->key.keysym.sym == SDLK_ESCAPE)
			game->popState();
	} 
}

void State_Menu::Update(float deltaTime) {
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	if (keyboard[SDL_SCANCODE_SPACE]) {
		game->pushState(new State_Gameplay());
	}

	blinking += 2 * deltaTime;
	if (blinking > 2.0f)
		blinking = 0.0f;
}

void State_Menu::Render() {
	string text = "PRESS SPACEBAR TO START";
	size_t x = text.length() * 8 / 2;
	
	if ((int)blinking == 1)
		font->renderString(game->getWidth() / 2 - 3 * (int)x, game->getHeight() / 3, text, 3);

	text = "RABBITS AND FLOWERS!";
	x = text.length() * 8 / 2;
	font->renderString(game->getWidth() / 2 - 3 * (int)x, game->getHeight() / 2, text, 3);
}

void State_Menu::Quit() {
	delete font;
	font = NULL;
	delete rm;
	rm = NULL;
}

bool State_Menu::isColliding(Object* thisObject, Object* other) {
	return false;
}

Player* State_Menu::getPlayer(int playerIndex) {
	return NULL; 
}

void State_Menu::setEndMode(int _winner, EndMode _endMode) {}