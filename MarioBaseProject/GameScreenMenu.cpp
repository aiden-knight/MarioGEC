#include "GameScreenMenu.h"

#include "Texture.h"
#include "GameData.h"
#include "Constants.h"

#include <iostream>

bool GameScreenMenu::SetUPLevel()
{
	m_backgroundTexture = new Texture(m_renderer);
	if (!m_backgroundTexture->LoadFromFile("Assets/not my art.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	return true;
}

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUPLevel();

	angle = 0.0f;
	flip = SDL_FLIP_NONE;
}

GameScreenMenu::~GameScreenMenu()
{
	delete m_backgroundTexture;
	m_backgroundTexture = nullptr;
}

void GameScreenMenu::Render()
{
	Vector2 position = { (SCREEN_WIDTH - m_backgroundTexture->GetWidth()) / 2.0f, (SCREEN_HEIGHT - m_backgroundTexture->GetHeight()) / 2.0f };
	m_backgroundTexture->Render(position, flip, angle);
}

void GameScreenMenu::Update(float deltaTime, const GameData* gameData)
{
	angle = gameData->angle;
	flip = (SDL_RendererFlip)(gameData->flipHoriz | gameData->flipVert);
}