#pragma once
#include "Components.h"
#include "SDL.h"
#include "..//TextureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect sourceRectangle, destinationRectangle;

	bool animated = false; //we need to know if the sprite is animated or not, by default it is set to false
	int frames = 0;
	int speed = 100; // this value is the delay in milliseconds

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	SpriteComponent(const char* path, int numberFrames, int mspeed)
	{
		animated = true;
		frames = numberFrames;
		speed = mspeed;
		setTexture(path);
	}

	~SpriteComponent()//deconstructor component
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void initialize() override
	{
		transform = &entity->getComponent<TransformComponent>();
		
		sourceRectangle.x = sourceRectangle.y = 0;
		sourceRectangle.w = transform->width;
		sourceRectangle.h = transform->height;
	}

	void update() override
	{
		if (animated)
		{
			sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		
		destinationRectangle.x = static_cast<int>(transform->position.x);
		destinationRectangle.y = static_cast<int>(transform->position.y);
		destinationRectangle.w = transform->width * transform->scale;
		destinationRectangle.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle);
	}
};