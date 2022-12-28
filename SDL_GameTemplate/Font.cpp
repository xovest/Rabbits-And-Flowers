#include "Font.h"
using namespace std;

Font::Font(Game* _game, SDL_Texture* _sheet, int _numCharsX, int _numCharsY, int _charWidth, int _charHeight) {
	game = _game;
	sheet = _sheet;
	numCharsX = _numCharsX;
	numCharsY = _numCharsY;
	charWidth = _charWidth;
	charHeight = _charHeight;
}

void Font::renderChar(int x, int y, unsigned char data, int fontSize) {
	SDL_Rect srcRect{}, destRect{};

	srcRect.x = (data % numCharsX) * charWidth;
	srcRect.y = (data / numCharsX) * charHeight;;
	srcRect.w = charWidth;
	srcRect.h = charHeight;

	destRect.x = x;
	destRect.y = y;
	destRect.w = charWidth * fontSize;
	destRect.h = charHeight * fontSize;

	SDL_RenderCopy(game->getRenderer(), sheet, &srcRect, &destRect);
}

void Font::renderString(int x, int y, string data, int fontSize) {
	for (int i = 0; i < data.length(); i++) {
		renderChar(x + i * charWidth * fontSize, y, data.at(i), fontSize);
	}
}

void Font::setColor(int red, int blue, int green) {
	SDL_SetTextureColorMod(sheet, red, blue, green);
}

void Font::resetColor() {
	SDL_SetTextureColorMod(sheet, 255, 255, 255);
}
