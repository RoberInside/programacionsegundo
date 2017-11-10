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
	
	//rectF = rect;
	SDL_RenderCopy(renderer, texture, nullptr, rect);

}
void Texture::renderFrame() {


	
}
