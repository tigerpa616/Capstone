#pragma once
#include <SDL.h>

class Collision
{
public:
	static bool AABB(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB); //True or False for whether or not something has been hit. Also going to check the x and y position of each rectangle and see if they are in bounds

};