#pragma once
#ifndef _CHARACTERMARIO
#define _CHARACTERMARIO

#include "Character.h"
class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2 startPosition);
	~CharacterMario();

	void Update(float deltaTime, const GameData* gameData) override;
	void Render() override;
};

#endif