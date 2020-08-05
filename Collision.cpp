#include "Collision.h"

bool Collision::AABB(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB)
{
	if (rectangleA.x + rectangleA.w >= rectangleB.x &&
		rectangleB.x + rectangleB.w >= rectangleA.x &&
		rectangleA.y + rectangleA.h >= rectangleB.y &&
		rectangleB.y + rectangleB.h >= rectangleA.y
		)
	{
		return true;
	}
	return false;
}