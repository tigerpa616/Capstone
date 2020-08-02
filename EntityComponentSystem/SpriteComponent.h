#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect sourceRectangle, destinationRectangle;

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void initialize() override
	{
		position = &entity->getComponent<PositionComponent>();
		
		sourceRectangle.x = sourceRectangle.y = 0;
		sourceRectangle.w = sourceRectangle.h = 32;
		destinationRectangle.w = destinationRectangle.h = 64;
	}

	void update() override
	{
		destinationRectangle.x = position->x();
		destinationRectangle.y = position->y();
	}

	void draw() override
	{
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle);
	}
};