#ifndef _H_FONT_H_
#define _H_FONT_H_
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

using namespace std;

class Font
{
private:
public:
	TTF_Font* font = nullptr;
	Font();
	
	~Font() { free(); }

	
	
	SDL_Rect rectFont;
	bool load(string filename, int	size);
	void free();
	
	SDL_Rect setRect(int h, int w, int x, int y);
	SDL_Surface* generateSurface(string	text, SDL_Color	color);		
	
};
#endif //! #ifndef _H_GAME_H_



