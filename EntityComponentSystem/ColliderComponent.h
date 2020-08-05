#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag; //will be used to tag collisions for later

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void initialize() override
	{
		if (!entity->hasComponent<TransformComponent>())//if the entity doesn't have the component type already
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();
	}

	void update()override
	{
		collider.x = static_cast<int> (transform->position.x);
		collider.y = static_cast<int> (transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
};