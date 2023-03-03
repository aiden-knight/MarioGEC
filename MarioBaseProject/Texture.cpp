#include "Texture.h"
#include <SDL_image.h>
#include <iostream>

Texture::Texture(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

Texture::~Texture()
{
	Free();

	m_renderer = nullptr;
}

bool Texture::LoadFromFile(std::string path)
{
	Free();

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		std::cout << "Unable to load image and create surface, image path: " << path << ". Error: " << IMG_GetError();
		return false;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));


	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	if (m_texture == nullptr)
	{
		std::cout << "Unable to create texture from surface, image path:  " << path << ". Error: " << IMG_GetError();
		return false;
	}
	m_width = surface->w;
	m_height = surface->h;

	SDL_FreeSurface(surface);
	return true;
}

void Texture::Free()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		
		m_texture = nullptr;
		m_width = 0.0f;
		m_height = 0.0f;
	}
}

void Texture::Render(Vector2 new_position, SDL_RendererFlip flip, double angle)
{
	SDL_Rect renderLocation = { new_position.x, new_position.y, m_width, m_height };
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, angle, nullptr, flip);
}