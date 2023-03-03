#include "GameScreenLevel1.h"

#include "Texture.h"
#include "GameData.h"
#include "Constants.h"

#include <iostream>

bool GameScreenLevel1::SetUPLevel()
{
	m_backgroundTexture = new Texture(m_renderer);
	if (!m_backgroundTexture->LoadFromFile("Assets/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	return true;
}

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUPLevel();

	angle = 0.0f;
	flip = SDL_FLIP_NONE;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_backgroundTexture;
	m_backgroundTexture = nullptr;
}

void GameScreenLevel1::Render()
{
	Vector2 position = { (SCREEN_WIDTH - m_backgroundTexture->GetWidth()) / 2.0f, (SCREEN_HEIGHT - m_backgroundTexture->GetHeight()) / 2.0f};
	m_backgroundTexture->Render(position, flip, angle);
}

void GameScreenLevel1::Update(float deltaTime, const GameData* gameData)
{
	angle = gameData->angle;
	flip = (SDL_RendererFlip) (gameData->flipHoriz | gameData->flipVert);
}