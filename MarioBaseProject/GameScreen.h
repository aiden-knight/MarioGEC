#pragma once
#ifndef _GAMESCREEN
#define _GAMESCREEN

#include <SDL.h>

struct GameData;

class GameScreen
{
protected:
	SDL_Renderer* m_renderer;
private:
public:
	GameScreen(SDL_Renderer* renderer);
	virtual ~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, const GameData* gameData);
};

#endif