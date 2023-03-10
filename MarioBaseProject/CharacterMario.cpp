#include "CharacterMario.h"
#include "GameData.h"
#include "Constants.h"
#include "Texture.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2 startPosition) : Character(renderer, imagePath, startPosition)
{
	m_facingDirection = FACING_RIGHT;
}
CharacterMario::~CharacterMario()
{

}

void CharacterMario::Update(float deltaTime, const GameData* gameData)
{
	if (gameData->keyData.upDown && m_canJump)
	{
		m_jumping = true;
		m_jumpForce = INITIAL_JUMP_FORCE;
	}

	if (m_jumping)
	{
		m_position.y -= m_jumpForce * deltaTime;

		m_jumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (m_jumpForce <= 0.0f)
			m_jumping = false;
	}

	if (gameData->keyData.leftDown)
	{
		m_position.x -= MOVEMENT_SPEED * deltaTime;
		m_facingDirection = FACING_LEFT;
	}
	if (gameData->keyData.rightDown)
	{
		m_position.x += MOVEMENT_SPEED * deltaTime;
		m_facingDirection = FACING_RIGHT;
	}

	AddGravity(deltaTime);
}

void CharacterMario::Render()
{
	if (m_facingDirection == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}