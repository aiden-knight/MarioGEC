//Be grateful for humble beginnings, because the next level will always require so much more of you

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Constants.h"
#include <iostream>

bool InitSDL(SDL_Window* window);
void CloseSDL(SDL_Window* window);

int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;

	if (InitSDL(window))
	{
		SDL_Delay(5000);
	}

	CloseSDL(window);

	return 0;
}

bool InitSDL(SDL_Window* window)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}

	window = SDL_CreateWindow("Legally Not Mario", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Window was not created. Error: " << SDL_GetError();
		return false;
	}
	
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "Failed to initialise SDL_image. SDL_image Error: " << IMG_GetError();
		return false;
	}

	return true;
}

void CloseSDL(SDL_Window* window)
{
	SDL_DestroyWindow(window);
	window = nullptr;

	IMG_Quit();
	SDL_Quit();
}