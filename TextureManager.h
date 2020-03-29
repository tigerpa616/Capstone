#pragma once
#include "Game.h"//We need SDL for this header file, so by including Game.h which already has SDL included its just more efficient 

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* rendwendy);
};
