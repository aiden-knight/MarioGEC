#pragma once
#ifndef _GAMESCREENMENU
#define _GAMESCREENMENU

#include "GameScreen.h"

class Texture;

class GameScreenMenu : GameScreen
{
private:
	Texture* m_backgroundTexture;

	bool SetUPLevel();
	float angle;
	SDL_RendererFlip flip;
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render() override;
	void Update(float deltaTime, const GameData* gameData) override;
};

#endif