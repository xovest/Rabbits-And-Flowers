#pragma once
#include <string>
#include "Game.h"
using namespace std;

class Font {
private:
	SDL_Texture* sheet;

	int charWidth;
	int charHeight;

	int numCharsX;
	int numCharsY;

	Game* game;
public:
	Font(Game* _game, SDL_Texture* _sheet, int _numCharsX, int _numCharsY, int _charWidth, int _charHeight);
	
	void renderChar(int x, int y, unsigned char data, int fontSize = 1);
	void renderString(int x, int y, string data, int fontSize = 1);

	void setColor(int red, int blue, int green);
	void resetColor();
};