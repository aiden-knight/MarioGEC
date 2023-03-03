#pragma once
#ifndef _GAMESCREENMANAGER
#define _GAMESCREENMANAGER

#include <SDL.h>
#include "Commons.h"

class GameScreen;
struct GameData;

class GameScreenManager
{
private:
	SDL_Renderer* m_renderer;

	GameScreen* m_currentScreen;
	SCREENS m_currentScreenEnum;
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, const GameData* gameData);

	void ChangeScreen(SCREENS newScreen);
};

#endif