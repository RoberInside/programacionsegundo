#ifndef _H_TEXTURE_H_
#define _H_TEXTURE_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Texture {
private:
	SDL_Texture* texture;
	SDL_Rect rectF, destRect; //rectangulo fuente y rectangulo destacado
	size_t _w = 0; // Texture width (pixels)
	size_t _h = 0; // Texture height (pixels)
	size_t _fw = 0; // Frame width (pixels)
	size_t _fh = 0; // Frame height (pixels)

public:
	Texture( size_t w, size_t h);
	~Texture();

	bool load(SDL_Renderer* renderer, string filename,
		size_t numRows = 1, size_t numCols = 1);

	void render(SDL_Renderer* renderer, const SDL_Rect& rect,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	void renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect,
		int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE); //por hacer

};
#endif
