#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	//renderer = rendywendy; No longer needed
	objectTexture = TextureManager::LoadTexture(textureSheet);

	xposition = x;
	yposition = y;
}

void GameObject::Update()
{
	xposition++;
	yposition++;

	sourceRectangle.h = 32;
	sourceRectangle.w = 32;
	sourceRectangle.x = 0;
	sourceRectangle.y = 0;

	destinationRectangle.x = xposition;
	destinationRectangle.y = yposition;
	destinationRectangle.w = sourceRectangle.w * 2;
	destinationRectangle.h = sourceRectangle.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
}