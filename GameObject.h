#pragma once
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, int x, int y);//no longer need SDL_Renderer* rendwendy, thanks to Game::renderer
	~GameObject();

	void Update();
	void Render();

private:
	int xposition;//where its gonna be on screen
	int yposition;//where its gonna be on screen

	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle, destinationRectangle;
	//SDL_Renderer* rendererPrivate; no longer needed

};
