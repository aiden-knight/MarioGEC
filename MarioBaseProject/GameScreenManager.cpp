#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenMenu.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_currentScreenEnum = NULL_SCREEN;

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
	if (m_currentScreenEnum == newScreen)
		return;

	if (m_currentScreen != nullptr)
	{
		delete m_currentScreen;
	}

	GameScreenLevel1* tempLevel1;
	GameScreenMenu* tempMenu;

	switch (newScreen)
	{
	case SCREEN_LEVEL1:
		m_currentScreenEnum = SCREEN_LEVEL1;

		tempLevel1 = new GameScreenLevel1(m_renderer);
		m_currentScreen = (GameScreen*)tempLevel1;
		tempLevel1 = nullptr;
		break;
	case SCREEN_MENU:
		m_currentScreenEnum = SCREEN_MENU;

		tempMenu = new GameScreenMenu(m_renderer);
		m_currentScreen = (GameScreen*)tempMenu;
		tempMenu = nullptr;
		break;
	}
}