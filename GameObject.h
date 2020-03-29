#pragma once
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, SDL_Renderer* rendywendy, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xposition;//where its gonna be on screen
	int yposition;//where its gonna be on screen

	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle, destinationRectangle;
	SDL_Renderer* renderer;

};
