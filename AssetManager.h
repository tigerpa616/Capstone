#pragma once
#include <map> //store the list of texture the game has
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "EntityComponentSystem/EntityComponentSystem.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	//the main thing this class will be responsible for will be creating the texture and building our game objects
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;

};