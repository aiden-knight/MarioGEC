#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;

	delete m_currentScreen;
	m_currentScreen = nullptr;
}

void GameScreenManager::Render()
{
	m_currentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, const GameData* gameData)
{
	m_currentScreen->Update(deltaTime, gameData);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (m_currentScreen != nullptr)
	{
		delete m_currentScreen;
	}

	GameScreenLevel1* tempScreen;
	switch (newScreen)
	{
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer);
		m_currentScreen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	}
}