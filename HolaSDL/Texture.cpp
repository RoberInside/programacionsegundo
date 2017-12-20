#include "Texture.h"
#include <iostream>

Texture::Texture(size_t const ROWS, size_t const COLS)
{
	texture = nullptr;
	_ROWS = ROWS;
	_COLS = COLS;
	textHeight = textWidth = 0;
	

}

Texture::Texture()
{
	texture = nullptr;
	_COLS = _ROWS = 1;
	textHeight = textWidth = 0;
	
}


Texture::~Texture()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}
bool Texture::load(SDL_Renderer* renderer, string filename) {

	bool success = true;
	SDL_Surface* tmpSur = nullptr;

	tmpSur = IMG_Load(filename.c_str());
	if (tmpSur == nullptr) { std::cout << "Unable to load image "<<filename<<" !" << endl; success = false; }
	else {
		texture = SDL_CreateTextureFromSurface(renderer, tmpSur);
		SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
		SDL_FreeSurface(tmpSur);
		success = texture != nullptr;
	}


	return success;

}
void Texture::render(SDL_Renderer* renderer, SDL_Rect* const &rect) {
	
	
	SDL_RenderCopy(renderer, texture, nullptr, rect);

}
void Texture::renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect,
	int row, int col, SDL_RendererFlip flip) const {

	SDL_Rect rect;
		
	rect.x = col * (textWidth  / _COLS);
	rect.y = row * (textHeight / _ROWS);
	rect.w = (textWidth/ _COLS);
	rect.h = (textHeight / _ROWS);
	SDL_RenderCopyEx(renderer, texture, &rect, &destRect, 0, 0, flip);
	
}

bool Texture::loadFromText(SDL_Renderer* renderer, const string text, SDL_Color color)
{
	SDL_Surface* textSurface = font.generateSurface(text, color);
	if (textSurface == nullptr)
		cout << "Unable	to	render	text	surface!	SDL_ttf	Error:	"
		<< TTF_GetError() << "\n";
	else {
		
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == nullptr) {
			cout << "Unable	to	create	texture	from	text!	SDL	Error:	"
				<< SDL_GetError() << "\n";
			textWidth = textHeight = 0;
		}
		else {
			textWidth = textSurface->w;
			textHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return	texture != nullptr;
}

bool Texture::loadFuente(string filename, int size)
{
	font.load(filename, size);
	return true;
}


