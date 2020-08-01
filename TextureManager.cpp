#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Surface* temporarySurface = IMG_Load(texture);
	SDL_Texture* texty = SDL_CreateTextureFromSurface(Game::renderer, temporarySurface);//replacing rendywendy with a static renderer instead
	SDL_FreeSurface(temporarySurface);

	return texty;
}
void TextureManager::Draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination)
{
	SDL_RenderCopy(Game::renderer, texture, &source, &destination);
};