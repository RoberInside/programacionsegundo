#ifndef _H_TEXTURE_H_
#define _H_TEXTURE_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Texture {
private:
	SDL_Texture* texture = nullptr;
	SDL_Rect destRect; //rectangulo fuente y rectangulo destino

	size_t frameW, frameH;

public:
	Texture();
	~Texture();

	bool load(SDL_Renderer* renderer, string filename);

	void render(SDL_Renderer* renderer, SDL_Rect* const &rect);

	void renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect,
		int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

};
#endif