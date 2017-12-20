#include "Font.h"



Font::Font()
{
	
}

bool Font::load(string filename, int size)
{
	
	font = TTF_OpenFont(filename.c_str(), size);
	return true;
}

void Font::free()
{
	
	if (font != nullptr)	
		 TTF_CloseFont(font);
	font = nullptr;
}

SDL_Surface* Font::generateSurface(string text, SDL_Color color) 
{
	return	TTF_RenderText_Solid(font, text.c_str(), color);
}
SDL_Rect Font::setRect(int h, int w, int x, int y) {
	
	rectFont.h = h;
	rectFont.w = w;
	rectFont.x = x;
	rectFont.y = y;
	
	return rectFont;
}


