#pragma once

#include <SDL.h>
#include "GameScreenManager.h"

struct KeyData
{
	bool aDown = false;
	bool dDown = false;
	bool qDown = false;
	bool fDown = false;
	bool gDown = false;
};

struct GameData
{
	SDL_Renderer* renderer = nullptr;

	GameScreenManager* gameScreenManager;

	SDL_Event e;
	bool exit = false;

	float angle = 0;
	Uint32 previousTime = 0;

	KeyData keyData;

	bool fPressed = false;
	bool gPressed = false;

	SDL_RendererFlip flipHoriz = SDL_FLIP_NONE;
	SDL_RendererFlip flipVert = SDL_FLIP_NONE;
};