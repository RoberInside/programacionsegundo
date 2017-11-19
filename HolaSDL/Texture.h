#ifndef _H_TEXTURE_H_
#define _H_TEXTURE_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Texture {

public:
	Texture(size_t const ROWS, size_t const COLS);
	Texture();
	~Texture();

	bool load(SDL_Renderer* renderer, string filename);

	void render(SDL_Renderer* renderer, SDL_Rect* const &rect);

	void renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect,
		int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

private:
	SDL_Texture* texture;
	SDL_Rect destRect; //rectangulo fuente y rectangulo destino

	int textWidth, textHeight;
	size_t  _ROWS, _COLS;
};
#endif