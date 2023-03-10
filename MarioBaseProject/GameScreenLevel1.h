#pragma once
#ifndef _GAMESCREENLEVEL1
#define _GAMESCREENLEVEL1

#include "GameScreen.h"

class Texture;
class Character;
class CharacterMario;

class GameScreenLevel1 : GameScreen
{
private:
	Texture* m_backgroundTexture;
	Character* m_luigi;
	CharacterMario* m_mario;

	bool SetUPLevel();
	float angle;
	SDL_RendererFlip flip;
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, const GameData* gameData) override;
};

#endif