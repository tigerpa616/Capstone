#include "Map.h"
#include "TextureManager.h"

int level_01[20][25] = { 
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	

};//temporary level until actual map replaces this (20 rows, 25 columns)

Map::Map()
{
	dirt = TextureManager::LoadTexture("assets/dirt.png");   //value 2
	grass = TextureManager::LoadTexture("assets/grass.png"); //value 1
	water = TextureManager::LoadTexture("assets/water.png"); //value 0

	LoadMap(level_01);

	source.x = source.y = 0; //starting position
	destination.w = source.w = 32;
	destination.h = source.h = 32;
	destination.x = destination.y = 0; //starting destination
}

void Map::LoadMap(int array[20][25]) //the point of the array is so we can load a map, which the array is essentially
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			map[row][column] = array[row][column]; //array[][] is whatever map is imputed, so for us it will be level_01
		}
	}
}

void Map::DrawMap()
{
	int type = 0;

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			type = map[row][column]; //type is now set to what the value of the 2d array is

			destination.x = column * 32;
			destination.y = row * 32;

			switch (type) //these cases will draw our textures
			{
			case 0:
				TextureManager::Draw(water, source, destination);
				break;
			case 1:
				TextureManager::Draw(grass, source, destination);
				break;
			case 2:
				TextureManager::Draw(dirt, source, destination);
				break;
			default:
				break;
			}

		}
	}
}