#pragma once
#include "Game.h"//We need SDL for this header file, so by including Game.h which already has SDL included its just more efficient 

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);//no longer need SDL_Renderer* rendwendy, thanks to Game::renderer
	static void Draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip flip);
};
