#include "Texture.h"
#include <iostream>

Texture::Texture()
{
	texture = nullptr;
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
	
	rect.x = frameW * col;
	rect.y = frameH * row;
	rect.w = frameW;
	rect.h = frameH;
	SDL_RenderCopyEx(renderer, texture, &rect, &destRect, 0, 0, flip);
	
}
