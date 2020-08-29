#pragma once
#include "EntityComponentSystem.h"
#include "SDL.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect sourceRectangle, destinationRectangle;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int sourceX, int sourceY, int xposition, int yposition, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		position.x = xposition;
		position.y = yposition;

		sourceRectangle.x = sourceX;
		sourceRectangle.y = sourceY;
		sourceRectangle.w = sourceRectangle.h = 32; //size of the tile we are taking

		destinationRectangle.x = xposition;
		destinationRectangle.y = yposition;
		destinationRectangle.w = destinationRectangle.h = 64;
	}

	void update() override
	{
		destinationRectangle.x = position.x - Game::camera.x;
		destinationRectangle.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
	}
};