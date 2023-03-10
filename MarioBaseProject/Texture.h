#pragma once
#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL.h>
#include <string>
#include "Commons.h"

class Texture
{
private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;

	int m_width;
	int m_height;

	void Free();
public:
	Texture(SDL_Renderer* renderer);
	~Texture();

	bool LoadFromFile(std::string path);
	void Render(Vector2 newPosition, SDL_RendererFlip flip, double angle = 0.0);

	int GetWidth() {return m_width;}
	int GetHeight() { return m_height; }
};

#endif