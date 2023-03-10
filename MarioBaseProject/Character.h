#pragma once
#ifndef _CHARACTER
#define _CHARACTER

#include <SDL.h>
#include <iostream>
#include "Commons.h"

class Texture;
struct GameData;

class Character
{
protected:
	SDL_Renderer* m_renderer;
	Vector2 m_position;
	Texture* m_texture;

	bool m_jumping;
	bool m_canJump;
	float m_jumpForce;
	FACING m_facingDirection;
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2 startPosition);
	virtual ~Character();

	virtual void Render();
	virtual void Update(float deltaTime, const GameData* gameData);
	virtual void AddGravity(float deltaTime);
	void SetPosition(Vector2 newPosition);
	Vector2 GetPosition();
};

#endif