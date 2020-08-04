#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
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
		transform = &entity->getComponent<TransformComponent>();
		
		sourceRectangle.x = sourceRectangle.y = 0;
		sourceRectangle.w = sourceRectangle.h = 32;
		destinationRectangle.w = destinationRectangle.h = 64;
	}

	void update() override
	{
		destinationRectangle.x = (int)transform->position.x;
		destinationRectangle.y = (int)transform->position.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle);
	}
};