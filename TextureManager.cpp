#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* rendywendy)
{
	SDL_Surface* temporarySurface = IMG_Load(texture);
	SDL_Texture* texty = SDL_CreateTextureFromSurface(rendywendy, temporarySurface);
	SDL_FreeSurface(temporarySurface);

	return texty;
};