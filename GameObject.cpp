#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* rendywendy, int x, int y)
{
	renderer = rendywendy;
	objectTexture = TextureManager::LoadTexture(textureSheet, rendywendy);

	xposition = x;
	yposition = y;
}

void GameObject::Update()
{
	xposition++;
	yposition++;

	sourceRectangle.h = 128;
	sourceRectangle.w = 128;
	sourceRectangle.x = 0;
	sourceRectangle.y = 0;

	destinationRectangle.x = xposition;
	destinationRectangle.y = yposition;
	destinationRectangle.w = sourceRectangle.w;
	destinationRectangle.h = sourceRectangle.h;
}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, objectTexture, &sourceRectangle, &destinationRectangle);
}