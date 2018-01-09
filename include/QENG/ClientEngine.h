#ifndef CLIENTENGINE_H
#define CLIENTENGINE_H

#include <string>
#include <functional>
#include "SDL.h"
#undef main

class ClientEngine
{
public:
	ClientEngine();
	/* void setSettings(); */
	/* void registerState(std::string tag, std::function<State()> state); */
	int run( /* std::string stateTag */ );
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // CLIENTENGINE_H
