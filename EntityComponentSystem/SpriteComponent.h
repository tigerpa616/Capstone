#pragma once
#include "Components.h"
#include "SDL.h"
#include "..//TextureManager.h"
#include "Animation.h"
#include <map>
#include "..//AssetManager.h"

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
	int animationIndex = 0; //default set to zero since if we don't animate our sprite then the initial y position needs to be at zero

	std::map<const char*, Animation > animations; //this will hold our animations

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(std::string id)
	{
		setTexture(id);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 500); //index 0, 3 frames, speed of 100 
		Animation walk = Animation(1, 8, 100); //index 1, 8 frames, speed of 100 
		Animation walkVertical = Animation(2, 3, 100); //index 2, x frames, speed of 100

		animations.emplace("Idle", idle); //figure out what emplace does
		animations.emplace("Walk", walk);
		animations.emplace("WalkVertical", walkVertical); //**GOTTA WORK ON THOSE ANIMATIONS**//

		
		Play("Idle");
		setTexture(id);
	}

	~SpriteComponent()//deconstructor component
	{

	}

	void setTexture(std::string id)
	{
		texture = Game::assets->GetTexture(id);
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

		sourceRectangle.y = animationIndex * transform->height;

		destinationRectangle.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destinationRectangle.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destinationRectangle.w = transform->width * transform->scale;
		destinationRectangle.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
	}

	void Play(const char* animationName)
	{
		//will be used to change the current frames and indexes that we need
		frames = animations[animationName].frames; //the char* that we put in will go through the frames find it in SpriteComponent and returns the information here
		animationIndex = animations[animationName].index;
		speed = animations[animationName].speed;

	}
};