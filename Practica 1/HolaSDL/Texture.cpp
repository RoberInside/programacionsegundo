#include "Texture.h"


Texture::Texture(size_t w, size_t h)
{
	texture = nullptr;
	_w = w;
	_h = h;
	w = 0;
	h = 0;
}


Texture::~Texture()
{
	texture = nullptr;
}
bool Texture::load(SDL_Renderer* renderer, string filename, size_t numRows = 1, size_t numCols = 1) {

	bool success = false;
	SDL_Surface* tmpSur = nullptr;

	tmpSur = IMG_Load(filename.c_str());

	texture = SDL_CreateTextureFromSurface(renderer, tmpSur);
	_h = tmpSur->clip_rect.h;
	_w = tmpSur->clip_rect.w;
	SDL_FreeSurface(tmpSur);
	success = texture != nullptr;


	return success;

}
void Texture::render(SDL_Renderer* renderer, const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) {
	
	//rectF = rect;
	SDL_RenderCopy(renderer, texture, &rectF, nullptr);

}
void Texture::renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE) {


	
}
