#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};

struct Rect
{
	float x;
	float y;
	float width;
	float height;

	Rect(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
};

enum SCREENS
{
	NULL_SCREEN,
	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT,
	FACING_RIGHT
};