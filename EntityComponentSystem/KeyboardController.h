#pragma once
#include "../Game.h"
#include "EntityComponentSystem.h"
#include "Components.h"

class keyboardController : public Component
{
public:
	TransformComponent* transform;

	void initialize() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override //Looking out for what keys we got
	{
		if (Game::event.type == SDL_KEYDOWN)//wasd movement
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			default:
				break;
			}
		}
	}
};
