#include "QENG/ClientEngine.h"

#include <iostream>

ClientEngine::ClientEngine():
	window(nullptr)
	, renderer(nullptr)
{
}

int ClientEngine::run()
{
	const int windowSize_x = 400, windowSize_y = 300;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		std::cout << "FATAL: Failed to initialize SDL" << std::endl;
		std::cout << "\t" << SDL_GetError();
		return 0;
	}

	window = SDL_CreateWindow("QENG Sample", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize_x, windowSize_y, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "FATAL: Failed to initialize SDL window" << std::endl;
		std::cout << "\t" << SDL_GetError();
		return 0;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "FATAL: Failed to initialize SDL renderer" << std::endl;
		std::cout << "\t" << SDL_GetError();
		return 0;
	}

	SDL_RenderSetLogicalSize(renderer, windowSize_x, windowSize_y);
	SDL_SetRenderDrawColor(renderer, 12, 23, 34, 45);

	bool runSample = true;
	while (runSample)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				runSample = false;
			}
		}
		SDL_Delay(7);

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
