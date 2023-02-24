//Be grateful for humble beginnings, because the next level will always require so much more of you

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Constants.h"
#include <iostream>
#include <string>


struct KeyData
{
	bool aDown = false;
	bool dDown = false;
	bool qDown = false;
	bool fDown = false;
	bool gDown = false;
};

struct GameData
{
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

	bool exit = false;

	float angle = 0;
	Uint32 previousTime = 0;

	bool fPressed = false;
	bool gPressed = false;

	SDL_RendererFlip flipHoriz = SDL_FLIP_NONE;
	SDL_RendererFlip flipVert = SDL_FLIP_NONE;
};

bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Texture*& texture);
void CloseSDL(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Texture*& texture);
void PollEvents(SDL_Event& e, KeyData* keyData, GameData* gameData);
void KeyboardInput(SDL_Keycode keyCode, KeyData* keyData, bool keyDown);
void Render(GameData* gameData);
bool LoadTextureFromFile(SDL_Renderer*& renderer, SDL_Texture*& texture, std::string path);
void FreeTexture(SDL_Texture*& texture);
void Update(KeyData* keyData, GameData* gameData);


int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;

	GameData gameData;

	if (!InitSDL(window, gameData.renderer, gameData.texture))
	{
		return 1;
	}

	KeyData keyData;
	gameData.previousTime = SDL_GetTicks();
	SDL_Event e;
	while (!gameData.exit)
	{
		PollEvents(e, &keyData, &gameData);
		Update(&keyData, &gameData);
		Render(&gameData);
	}

	CloseSDL(window, gameData.renderer, gameData.texture);

	return 0;
}

void Update(KeyData* keyData, GameData* gameData)
{
	int deltaTime = SDL_GetTicks() - gameData->previousTime;

	float speed = 50;

	if (keyData->aDown)
	{
		gameData->angle -= speed * deltaTime / 1000.0f;
	}
	if (keyData->dDown)
	{
		gameData->angle += speed * deltaTime / 1000.0f;
	}

	if (keyData->qDown)
	{
		gameData->exit = true;
	}

	if (keyData->fDown && !gameData->fPressed)
	{
		if (gameData->flipHoriz == SDL_FLIP_NONE)
		{
			gameData->flipHoriz = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			gameData->flipHoriz = SDL_FLIP_NONE;
		}
		
		gameData->fPressed = true;
	}
	else if(!keyData->fDown && gameData->fPressed)
	{
		gameData->fPressed = false;
	}

	if (keyData->gDown && !gameData->gPressed)
	{
		if (gameData->flipVert == SDL_FLIP_NONE)
		{
			gameData->flipVert = SDL_FLIP_VERTICAL;
		}
		else
		{
			gameData->flipVert = SDL_FLIP_NONE;
		}

		gameData->gPressed = true;
	}
	else if (!keyData->gDown && gameData->gPressed)
	{
		gameData->gPressed = false;
	}

	gameData->previousTime = SDL_GetTicks();
}

void Render(GameData* gameData)
{
	SDL_SetRenderDrawColor(gameData->renderer, 0x00, 0x00, 0xAA, 0xFF);
	SDL_RenderClear(gameData->renderer);

	SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	SDL_RenderCopyEx(gameData->renderer, gameData->texture, NULL, &renderLocation, gameData->angle, NULL, (SDL_RendererFlip) (gameData->flipHoriz | gameData->flipVert));
	SDL_RenderPresent(gameData->renderer);
}

bool LoadTextureFromFile(SDL_Renderer*& renderer, SDL_Texture*& texture, std::string path)
{
	FreeTexture(texture);

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		std::cout << "Unable to load image and create surface, image path: " << path << ". Error: " << IMG_GetError();
		return false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		std::cout << "Unable to create texture from surface, image path:  " << path << ". Error: " << IMG_GetError();
		return false;
	}

	SDL_FreeSurface(surface);
	return true;
}

void FreeTexture(SDL_Texture*& texture)
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void PollEvents(SDL_Event& e, KeyData* keyData, GameData* gameData)
{
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			gameData->exit = true;
			break;
		case SDL_KEYDOWN:
			KeyboardInput(e.key.keysym.sym, keyData, true);
			break;
		case SDL_KEYUP:
			KeyboardInput(e.key.keysym.sym, keyData, false);
			break;
		}
	}
}

void KeyboardInput(SDL_Keycode keyCode, KeyData* keyData, bool keyDown)
{
	switch (keyCode)
	{
	case SDLK_a:
		keyData->aDown = keyDown;
		break;
	case SDLK_d:
		keyData->dDown = keyDown;
		break;
	case SDLK_q:
		keyData->qDown = keyDown;
		break;
	case SDLK_f:
		keyData->fDown = keyDown;
		break;
	case SDLK_g:
		keyData->gDown = keyDown;
		break;
	}
}

bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Texture*& texture)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}

	window = SDL_CreateWindow("Legally Not Mario", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Window was not created. Error: " << SDL_GetError();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "Renderer was not created. Error: " << SDL_GetError();
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "Failed to initialise SDL_image. SDL_image Error: " << IMG_GetError();
		return false;
	}

	if (!LoadTextureFromFile(renderer, texture, "Assets/test.bmp"))
	{
		return false;
	}

	return true;
}

void CloseSDL(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Texture*& texture)
{
	SDL_DestroyWindow(window);
	window = nullptr;
	
	FreeTexture(texture);

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}