#include "Collision.h"
#include "EntityComponentSystem\ColliderComponent.h"

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

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		//std::cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}