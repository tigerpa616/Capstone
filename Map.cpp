#include "Map.h"
#include "Game.h"
#include <fstream>//allows us to read our map externally
#include "EntityComponentSystem/EntityComponentSystem.h"
#include "EntityComponentSystem/Components.h"

extern Manager manager; //object named manager defined someplace else

Map::Map(std::string tID, int ms, int ts) : textureID(tID), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) //the point of the array is so we can load a map
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int sourceX, sourceY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			sourceY = atoi(&c) * tileSize;
			
			mapFile.get(c);
			sourceX = atoi(&c) * tileSize;

			AddTile(sourceX, sourceY, x *scaledSize, y * scaledSize);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::AddTile(int sourceX, int sourceY, int xPosition, int yPosition) 
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(sourceX, sourceY, xPosition, yPosition, tileSize, mapScale, textureID);//This is how we will add a tile
	tile.addGroup(Game::groupMap);
}