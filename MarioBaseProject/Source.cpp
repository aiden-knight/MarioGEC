//Be grateful for humble beginnings, because the next level will always require so much more of you

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Constants.h"
#include "Texture.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "GameData.h"

#include <iostream>
#include <string>

bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void CloseSDL(SDL_Window*& window, GameData* gameData);
void PollEvents(GameData* gameData);
void KeyboardInput(SDL_Keycode keyCode, KeyData* keyData, bool keyDown);
void Render(GameData* gameData);
void Update(GameData* gameData);

int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;

	GameData gameData;

	if (!InitSDL(window, gameData.renderer))
	{
		return 1;
	}

	KeyData keyData;
	gameData.gameScreenManager = new GameScreenManager(gameData.renderer, SCREEN_MENU);
	gameData.previousTime = SDL_GetTicks();
	while (!gameData.exit)
	{
		PollEvents(&gameData);
		Update(&gameData);
		Render(&gameData);
	}

	CloseSDL(window, &gameData);

	return 0;
}

void Update(GameData* gameData)
{
	Uint32 newTime = SDL_GetTicks();
	int deltaTime = SDL_GetTicks() - gameData->previousTime;

	float speed = 50;

	if (gameData->keyData.aDown)
	{
		gameData->angle -= speed * deltaTime / 1000.0f;
	}
	if (gameData->keyData.dDown)
	{
		gameData->angle += speed * deltaTime / 1000.0f;
	}

	if (gameData->keyData.qDown)
	{
		gameData->exit = true;
	}

	if (gameData->keyData.fDown && !gameData->fPressed)
	{
		if (gameData->flipHoriz == SDL_FLIP_NONE)
		{
			gameData->flipHoriz = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			gameData->flipHoriz = SDL_FLIP_NONE;
		}
		
		gameData->fPressed = true;
	}
	else if(!gameData->keyData.fDown && gameData->fPressed)
	{
		gameData->fPressed = false;
	}

	if (gameData->keyData.gDown && !gameData->gPressed)
	{
		if (gameData->flipVert == SDL_FLIP_NONE)
		{
			gameData->flipVert = SDL_FLIP_VERTICAL;
		}
		else
		{
			gameData->flipVert = SDL_FLIP_NONE;
		}

		gameData->gPressed = true;
	}
	else if (!gameData->keyData.gDown && gameData->gPressed)
	{
		gameData->gPressed = false;
	}

	if (gameData->keyData.pDown)
	{
		gameData->gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
	}
	else if (gameData->keyData.oDown)
	{
		gameData->gameScreenManager->ChangeScreen(SCREEN_MENU);
	}

	gameData->gameScreenManager->Update((float)(newTime - gameData->previousTime) / 1000.0f, gameData);
	gameData->previousTime = SDL_GetTicks();
}

void Render(GameData* gameData)
{
	SDL_SetRenderDrawColor(gameData->renderer, 0x00, 0x00, 0xAA, 0xFF);
	SDL_RenderClear(gameData->renderer);

	gameData->gameScreenManager->Render();

	SDL_RenderPresent(gameData->renderer);
}

void PollEvents(GameData* gameData)
{
	while (SDL_PollEvent(&gameData->e) != 0)
	{
		switch (gameData->e.type)
		{
		case SDL_QUIT:
			gameData->exit = true;
			break;
		case SDL_KEYDOWN:
			KeyboardInput(gameData->e.key.keysym.sym, &gameData->keyData, true);
			break;
		case SDL_KEYUP:
			KeyboardInput(gameData->e.key.keysym.sym, &gameData->keyData, false);
			break;
		}
	}
}

void KeyboardInput(SDL_Keycode keyCode, KeyData* keyData, bool keyDown)
{
	switch (keyCode)
	{
	case SDLK_a:
		keyData->aDown = keyDown;
		break;
	case SDLK_d:
		keyData->dDown = keyDown;
		break;
	case SDLK_q:
		keyData->qDown = keyDown;
		break;
	case SDLK_f:
		keyData->fDown = keyDown;
		break;
	case SDLK_g:
		keyData->gDown = keyDown;
		break;
	case SDLK_p:
		keyData->pDown = keyDown;
		break;
	case SDLK_o:
		keyData->oDown = keyDown;
		break;
	case SDLK_w:
		keyData->wDown = keyDown;
		break;
	}
}

bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer)
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

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "Renderer was not created. Error: " << SDL_GetError();
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

void CloseSDL(SDL_Window*& window, GameData* gameData)
{
	SDL_DestroyWindow(window);
	window = nullptr;
	
	delete gameData->gameScreenManager;
	gameData->gameScreenManager = nullptr;

	SDL_DestroyRenderer(gameData->renderer);
	gameData->renderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}