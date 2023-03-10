#include "Character.h"
#include "Texture.h"
#include "GameData.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2 startPosition)
{
	m_renderer = renderer;
	m_position = startPosition;

	m_texture = new Texture(renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load Character texture!" << std::endl;
	}

	m_facingDirection = FACING_RIGHT;
}

Character::~Character()
{
	m_renderer = nullptr;
	delete m_texture;
}


void Character::Render()
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

void Character::Update(float deltaTime, const GameData* gameData)
{
	if (gameData->keyData.wDown && m_canJump)
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

	if (gameData->keyData.aDown)
	{
		m_position.x -= MOVEMENT_SPEED * deltaTime;
		m_facingDirection = FACING_LEFT;
	}
	if (gameData->keyData.dDown)
	{
		m_position.x += MOVEMENT_SPEED * deltaTime;
		m_facingDirection = FACING_RIGHT;
	}

	AddGravity(deltaTime);
}

void Character::AddGravity(float deltaTime)
{
	m_position.y += GRAVITY * deltaTime;
	if (m_position.y >= SCREEN_HEIGHT - m_texture->GetHeight())
	{
		m_position.y = SCREEN_HEIGHT - m_texture->GetHeight();
		m_canJump = true;
	}
}

void Character::SetPosition(Vector2 newPosition)
{
	m_position = newPosition;
}

Vector2 Character::GetPosition()
{
	return m_position;
}