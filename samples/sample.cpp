
#include "SDL.h"
#undef main

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("QENG Sample", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 300, SDL_WINDOW_SHOWN);

	SDL_Delay(2000);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
