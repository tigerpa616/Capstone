#pragma once
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public: 
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRectangle;
	int tileID;
	const char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRectangle.x = x;
		tileRectangle.y = y;
		tileRectangle.w = w;
		tileRectangle.h = h;
		tileID = id; //automatically assigning the texture when we create a tile


		switch (tileID)
		{
		case 0:
			path = "assets/dirt.png";
			break;
		case 1:
			path = "assets/grass.png";
			break;
		case 2:
			path = "assets/water.png";
			break;
		default:
			break;
		}
	}

	void initialize() override
	{
		entity->addComponent<TransformComponent>((float)tileRectangle.x, (float)tileRectangle.y, tileRectangle.w, tileRectangle.h, 1); //will add the transform component to our tile
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};