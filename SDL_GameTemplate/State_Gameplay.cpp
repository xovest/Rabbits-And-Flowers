#include "State_Gameplay.h"
#include "Random.h"

bool State_Gameplay::Init(Game* _game) {
	game = _game;
	endMode = EndMode::PLAY_MODE;

	game->getStats()->SetP1Score();
	game->getStats()->SetP2Score();
	game->getStats()->SetGameplayTime();
	game->getStats()->SetStateGameplayEnd(EndMode::PLAY_MODE);

	rm = new ResourceManager(game);
	try { // each texture
		rm->loadTexture("assets/bunnies.png");
		rm->loadTexture("assets/font_texture.png");
		rm->loadTexture("assets/map.png");
		rm->loadTexture("assets/flower01.png"); 
		rm->loadTexture("assets/flower02.png");
		rm->loadTexture("assets/flower03.png");
		rm->loadTexture("assets/flower04.png");
		rm->loadTexture("assets/flower05.png");
		rm->loadTexture("assets/carrot.png");
	} catch (runtime_error &e) {
		cerr << e.what() << endl;
		return false;
	}

	font = new Font(game, rm->getTexture("assets/font_texture.png"), 16, 16, 8, 16);
	timer = new Timer();
	level = new Level(game, rm, timer);
	level->init();

	Player1.init(game, rm, 1, CFG::P1_SPAWN_POS_X, CFG::P1_SPAWN_POS_Y);
	Player2.init(game, rm, 2, CFG::P2_SPAWN_POS_X, CFG::P2_SPAWN_POS_Y);

	for (unsigned int i = 0; i < CFG::MAX_FLOWERS_DEAD; i++) {
		flowers_dead.push_back(new Flower_Dead());
		flowers_dead.back()->init(game, rm);

		while (collideWithOtherObjects(flowers_dead.back())) {
			flowers_dead.back()->spawn();
		}
	}
	for (unsigned int i = 0; i < CFG::MAX_CARROTS; i++) {
		carrots.push_back(new Carrot());
		carrots.back()->init(game, rm);

		while (collideWithOtherObjects(carrots.back())) {
			carrots.back()->relocate();
		}
	}
	for (unsigned int i = 0; i < CFG::MAX_FLOWERS_SLOW; i++) {
		flowers_slow.push_back(new Flower_Slow());
		flowers_slow.back()->init(game, rm);

		while (collideWithOtherObjects(flowers_slow.back())) {
			flowers_slow.back()->spawn();
		}
	}
	for (unsigned int i = 0; i < CFG::MAX_FLOWERS_MAD; i++) {
		flowers_mad.push_back(new Flower_Mad());
		flowers_mad.back()->init(game, rm);

		while (collideWithOtherObjects(flowers_mad.back())) {
			flowers_mad.back()->spawn();
		}
	}
	for (unsigned int i = 0; i < CFG::MAX_FLOWERS_INVERTED; i++) {
		flowers_inverted.push_back(new Flower_Inverted());
		flowers_inverted.back()->init(game, rm);

		while (collideWithOtherObjects(flowers_inverted.back())) {
			flowers_inverted.back()->spawn();
		}
	}
	for (unsigned int i = 0; i < CFG::MAX_FLOWERS_SPEED; i++) {
		flowers_speed.push_back(new Flower_Speed());
		flowers_speed.back()->init(game, rm);

		while (collideWithOtherObjects(flowers_speed.back())) {
			flowers_speed.back()->spawn();
		}
	}
	return true;
}

void State_Gameplay::HandleEvents(SDL_Event* event) {
	if (event->type == SDL_QUIT)
		game->setQuit();
	else if (event->type == SDL_KEYDOWN) {
		if (event->key.keysym.sym == SDLK_ESCAPE)
			game->popState();
	}
}

void State_Gameplay::Update(float deltaTime) {
	if (endMode == EndMode::FINISHED) {
		game->popState();
	} else {
		const Uint8* keyboard = SDL_GetKeyboardState(NULL);

		int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

		// keys
		if (keyboard[SDL_SCANCODE_UP])
			y1--;
		if (keyboard[SDL_SCANCODE_DOWN])
			y1++;
		if (keyboard[SDL_SCANCODE_LEFT])
			x1--;
		if (keyboard[SDL_SCANCODE_RIGHT])
			x1++;

		if (keyboard[SDL_SCANCODE_W])
			y2--;
		if (keyboard[SDL_SCANCODE_S])
			y2++;
		if (keyboard[SDL_SCANCODE_A])
			x2--;
		if (keyboard[SDL_SCANCODE_D])
			x2++;

		if (x1 || y1)
			Player1.move(x1, y1);
		
		if (x2 || y2)
			Player2.move(x2, y2);

		Player1.update(deltaTime);
		Player2.update(deltaTime);

		// carrot
		for (int i = 0; i < carrots.size(); i++) {
			carrots[i]->update(deltaTime);

			if (isColliding(&Player1, carrots[i])) {
				Player1.setScore(1);

				if (game->getStats()->GetP1Victories() == 0) {
					if (Player1.getScore() == 10)
						setEndMode(1, EndMode::NORMAL_END);
				}
				else if (game->getStats()->GetP1Victories() == 1) {
					Player2.incrementSpeed();
					if (Player1.getScore() == 20)
						setEndMode(1, EndMode::NORMAL_END);
				}
				else if (game->getStats()->GetP1Victories() == 2) {
					Player2.incrementSpeed();
					Player2.incrementSpeed();
					if (Player1.getScore() == 30)
						setEndMode(1, EndMode::NORMAL_END);
				}

				while (collideWithOtherObjects(carrots[i])) {
					carrots[i]->relocate();
				}
			}

			if (isColliding(&Player2, carrots[i])) {
				Player2.setScore(1);
				
				if (game->getStats()->GetP2Victories() == 0) {
					if (Player2.getScore() == 10)
						setEndMode(2, EndMode::NORMAL_END);
				}
				else if (game->getStats()->GetP2Victories() == 1) {
					Player1.incrementSpeed();
					if (Player2.getScore() == 20)
						setEndMode(2, EndMode::NORMAL_END);
				}
				else if (game->getStats()->GetP2Victories() == 2) {
					Player1.incrementSpeed();
					Player1.incrementSpeed();
					if (Player2.getScore() == 30)
						setEndMode(2, EndMode::NORMAL_END);
				}

				while (collideWithOtherObjects(carrots[i])) {
					carrots[i]->relocate();
				}
			}
		}

		// flower dead
		for (int i = 0; i < flowers_dead.size(); i++) {
			flowers_dead[i]->update();

			if (isColliding(&Player1, flowers_dead[i])) {
				flowers_dead[i]->spawn(true);
				setEndMode(2, EndMode::NORMAL_END);

			} else if (isColliding(&Player2, flowers_dead[i])) {
				flowers_dead[i]->spawn(true);
				setEndMode(1, EndMode::NORMAL_END);
			}
		}

		// flower slow
		for (int i = 0; i < flowers_slow.size(); i++) {
			flowers_slow[i]->update();

			if (isColliding(&Player1, flowers_slow[i])) {
				if (game->getStats()->GetP1Victories() == 0) {
					Player1.decrementSpeed(CFG::SPEED_DECREASE);

					if (Player1.isMad()) {
						Player1.increasePoisonTime(CFG::POISON_TIME_INCREASE);
						Player1.increasePoisonTime(CFG::POISON_TIME_INCREASE);
					}
				}
				else if (game->getStats()->GetP1Victories() == 1) {
					Player1.decrementSpeed(CFG::SPEED_DECREASE);
					Player1.decrementSpeed(CFG::SPEED_DECREASE);

					if (Player1.isMad()) {
						Player1.increasePoisonTime(CFG::POISON_TIME_INCREASE);
					}
				}
				else if (game->getStats()->GetP1Victories() == 2) {
					Player1.decrementSpeed(CFG::SPEED_DECREASE);
					Player1.decrementSpeed(CFG::SPEED_DECREASE);
					Player1.decrementSpeed(CFG::SPEED_DECREASE);
				}

				while (collideWithOtherObjects(flowers_slow[i])) {
					flowers_slow[i]->spawn();
				}
			} else if (isColliding(&Player2, flowers_slow[i])) {
				if (game->getStats()->GetP2Victories() == 0) {
					Player2.decrementSpeed(CFG::SPEED_DECREASE);

					if (Player2.isMad()) {
						Player2.increasePoisonTime(CFG::POISON_TIME_INCREASE);
						Player2.increasePoisonTime(CFG::POISON_TIME_INCREASE);
					}
				}
				else if (game->getStats()->GetP2Victories() == 1) {
					Player2.decrementSpeed(CFG::SPEED_DECREASE);
					Player2.decrementSpeed(CFG::SPEED_DECREASE);

					if (Player2.isMad()) {
						Player2.increasePoisonTime(CFG::POISON_TIME_INCREASE);
					}
				}
				else if (game->getStats()->GetP2Victories() == 2) {
					Player2.decrementSpeed(CFG::SPEED_DECREASE);
					Player2.decrementSpeed(CFG::SPEED_DECREASE);
					Player2.decrementSpeed(CFG::SPEED_DECREASE);
				}

				while (collideWithOtherObjects(flowers_slow[i])) {
					flowers_slow[i]->spawn();
				}
			}
		}

		// flower mad
		for (int i = 0; i < flowers_mad.size(); i++) {
			flowers_mad[i]->update();

			if (isColliding(&Player1, flowers_mad[i])) {
				flowers_mad[i]->spawn(true);
				Player1.setMadMode(true);
			} else if (isColliding(&Player2, flowers_mad[i])) {
				flowers_mad[i]->spawn(true);
				Player2.setMadMode(true);
			}
		}

		// flower invert
		for (int i = 0; i < flowers_inverted.size(); i++) {
			flowers_inverted[i]->update();

			if (isColliding(&Player1, flowers_inverted[i])) {
				if (game->getStats()->GetP1Victories() == 0) {
					Player1.setInvertedControls(CFG::INVERTED_CONTROLS_TIME / 2);
					Player2.setInvertedControls(CFG::INVERTED_CONTROLS_TIME);
				}
				else if (game->getStats()->GetP1Victories() == 1) {
					Player1.setInvertedControls(CFG::INVERTED_CONTROLS_TIME);
					Player2.setInvertedControls(CFG::INVERTED_CONTROLS_TIME / 2);
				}
				else if (game->getStats()->GetP1Victories() == 2) {
					Player1.setInvertedControls(CFG::INVERTED_CONTROLS_TIME * 2);
				}

				while (collideWithOtherObjects(flowers_inverted[i])) {
					flowers_inverted[i]->spawn();
				}
			} else if (isColliding(&Player2, flowers_inverted[i])) {
				if (game->getStats()->GetP2Victories() == 0) {
					Player2.setInvertedControls(CFG::INVERTED_CONTROLS_TIME / 2);
					Player1.setInvertedControls(CFG::INVERTED_CONTROLS_TIME);
				}
				else if (game->getStats()->GetP2Victories() == 1) {
					Player2.setInvertedControls(CFG::INVERTED_CONTROLS_TIME);
					Player1.setInvertedControls(CFG::INVERTED_CONTROLS_TIME / 2);
				}
				else if (game->getStats()->GetP2Victories() == 2) {
					Player2.setInvertedControls(CFG::INVERTED_CONTROLS_TIME * 2);
				}

				while (collideWithOtherObjects(flowers_inverted[i])) {
					flowers_inverted[i]->spawn();
				}
			}
		}

		// flower speed
		for (int i = 0; i < flowers_speed.size(); i++) {
			flowers_speed[i]->update();

			if (isColliding(&Player1, flowers_speed[i])) {
				if (game->getStats()->GetP1Victories() == 0) {
					Player1.incrementSpeed();
					Player1.incrementSpeed();
					Player1.incrementSpeed();
					Player1.setScore(-1);
				}
				else if (game->getStats()->GetP1Victories() == 1) {
					Player1.incrementSpeed();
					Player1.incrementSpeed();
					Player1.setScore(-2);
				}
				else if (game->getStats()->GetP1Victories() == 2) {
					Player1.incrementSpeed();
					Player1.setScore(-3);
				}

				while (collideWithOtherObjects(flowers_speed[i])) {
					flowers_speed[i]->spawn();
				}
			} else if (isColliding(&Player2, flowers_speed[i])) {
				if (game->getStats()->GetP2Victories() == 0) {
					Player2.incrementSpeed();
					Player2.incrementSpeed();
					Player2.incrementSpeed();
					Player2.setScore(-1);
				}
				else if (game->getStats()->GetP2Victories() == 1) {
					Player2.incrementSpeed();
					Player2.incrementSpeed();
					Player2.setScore(-2);
				}
				else if (game->getStats()->GetP2Victories() == 2) {
					Player2.incrementSpeed();
					Player2.setScore(-3);
				}

				while (collideWithOtherObjects(flowers_speed[i])) {
					flowers_speed[i]->spawn();
				}
			}
		}

		//time
		if (timer->getTime() == 60000)
			setEndMode(0, EndMode::NORMAL_END);

		// end
		theEnd();
	}
}

void State_Gameplay::Render() {
	level->render();

	font->setColor(CFG::PLAYER_FONT_1.r, CFG::PLAYER_FONT_1.g, CFG::PLAYER_FONT_1.b);
	font->renderString(97, 5, to_string((int)Player1.getScore()));
	font->renderString(194, 5, to_string((int)Player1.getSpeed()));

	font->setColor(CFG::PLAYER_FONT_2.r, CFG::PLAYER_FONT_2.g, CFG::PLAYER_FONT_2.b);
	font->renderString((game->getWidth() / 2) + 97 - 135, 5, to_string((int)Player2.getScore()));
	font->renderString((game->getWidth() / 2) + 194 - 135, 5, to_string((int)Player2.getSpeed()));
	
	Player1.render();
	Player2.render();

	font->resetColor();

	for (int i = 0; i < carrots.size(); i++) {
		carrots[i]->render();
	}
	for (int i = 0; i < flowers_dead.size(); i++) {
		flowers_dead[i]->render();
	}
	for (int i = 0; i < flowers_slow.size(); i++) {
		flowers_slow[i]->render();
	}
	for (int i = 0; i < flowers_mad.size(); i++) {
		flowers_mad[i]->render();
	}
	for (int i = 0; i < flowers_inverted.size(); i++) {
		flowers_inverted[i]->render();
	}
	for (int i = 0; i < flowers_speed.size(); i++) {
		flowers_speed[i]->render();
	}
}

void State_Gameplay::Quit() {
	for (int i = 0; i < carrots.size(); i++) {
		delete carrots[i];
	}
	carrots.clear();

	for (int i = 0; i < flowers_dead.size(); i++) {
		delete flowers_dead[i];
	}
	flowers_dead.clear();

	for (int i = 0; i < flowers_slow.size(); i++) {
		delete flowers_slow[i];
	}
	flowers_slow.clear();

	for (int i = 0; i < flowers_mad.size(); i++) {
		delete flowers_mad[i];
	}
	flowers_mad.clear();

	for (int i = 0; i < flowers_inverted.size(); i++) {
		delete flowers_inverted[i];
	}
	flowers_inverted.clear();

	for (int i = 0; i < flowers_speed.size(); i++) {
		delete flowers_speed[i];
	}
	flowers_speed.clear();
	
	delete font;
	font = NULL;

	delete level;
	level = NULL;

	delete timer;
	timer = NULL;

	delete rm;
	rm = NULL;
}

bool State_Gameplay::isColliding(Object* thisObject, Object* other) {
	if (thisObject == other) {
		return false;
	}
	else if (thisObject->collideWith(other)) {
		return true;
	}

	return false;
}

Player* State_Gameplay::getPlayer(int currnetPlayerIndex) {
	if (currnetPlayerIndex == 1) {
		return &Player2;
	} else if (currnetPlayerIndex == 2) {
		return &Player1;
	} else {
		return NULL;
	}
}

void State_Gameplay::theEnd() {
	game->getStats()->SetP1Score(Player1.getScore());
	game->getStats()->SetP2Score(Player2.getScore());
	game->getStats()->SetGameplayTime(timer->getTime());
	game->getStats()->SetStateGameplayEnd(endMode);

	if (endMode != EndMode::PLAY_MODE)  {
		SDL_SetRenderDrawColor(game->getRenderer(), 83, 181, 100, CFG::PLAYER_1.a);
		SDL_RenderClear(game->getRenderer());

		stringstream txt;
		if (winner == 0)
			txt << "    Time is up!";
		else
			txt << "Player " << winner << " has won!";

		streamsize txtSize = txt.str().size() * 64;
		font->setColor(CFG::WHITE_COLOR.r, CFG::WHITE_COLOR.g, CFG::WHITE_COLOR.b);
		font->renderString(game->getWidth() / 4, game->getHeight() / 4, txt.str(), 3);

		SDL_RenderPresent(game->getRenderer());
		SDL_Delay(1000);
		
		endMode = EndMode::FINISHED;
		game->pushState(new State_End());
	}
}

void State_Gameplay::setEndMode(int _winner, EndMode _endMode) {
	winner = _winner;

	if (winner == 1) {
		game->getStats()->P1AddVictory();
	} else if (winner == 2) {
		game->getStats()->P2AddVictory();
	}

	endMode = _endMode;
}

bool State_Gameplay::collideWithOtherObjects(Object* object) {
	if (isColliding(object, &Player1) || isColliding(object, &Player2)) {
		return true;
	}

	for (int i = 0; i < flowers_dead.size(); i++) {
		if (isColliding(object, flowers_dead[i])) {
			return true;
		}
	}

	for (int i = 0; i < flowers_slow.size(); i++) {
		if (isColliding(object, flowers_slow[i])) {
			return true;
		}
	}

	for (int i = 0; i < flowers_mad.size(); i++) {
		if (isColliding(object, flowers_mad[i])) {
			return true;
		}
	}

	for (int i = 0; i < flowers_inverted.size(); i++) {
		if (isColliding(object, flowers_inverted[i])) {
			return true;
		}
	}

	for (int i = 0; i < carrots.size(); i++) {
		if (isColliding(object, carrots[i])) {
			return true;
		}
	}

	return false;
}
