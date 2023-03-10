#pragma once
#ifndef _COLLISIONS
#define _COLLISIONS

#include "Commons.h"

class Character;

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();
	bool Circle(Character* character1, Character* character2);
	bool Box(Rect rect1, Rect rect2);
};


#endif