/**************************************************
* Borja Cano Álvarez					          *
* Roberto Alcázar Morales                         *
* Desarrolo de Videjuegos UCM                     *  
* Practica 1 - PACMAN -                           *
* Using SDL Library from https://www.libsdl.org/  *
* by Sam Lantinga                                 *
**************************************************/


#include "Game.h"

int main(int argc, char* argv[]){
	Game* game = new Game;
	game->run();
	return 0;
}