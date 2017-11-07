#include "GameObject.h"

void GameObject::render() {
	rect.x = pos.x + (rect.w / 2);
	rect.y = pos.y + (rect.h / 2);

	texture->render(game->getRenderer(), rect, SDL_FLIP_NONE);
}
