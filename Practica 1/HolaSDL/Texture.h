#ifndef _H_TEXTURE_H_
#define _H_TEXTURE_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Texture {
private:
	SDL_Texture* texture = nullptr;
	SDL_Rect rectF, destRect; //rectangulo fuente y rectangulo destacado

public:
	Texture();
	~Texture();

	bool load(SDL_Renderer* renderer, string filename);

	void render(SDL_Renderer* renderer, SDL_Rect* const &rect);

	void renderFrame(/*TODO*/); //por hacer

};
#endif