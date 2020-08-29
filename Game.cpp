#include "Game.h"
#include "TextureManager.h"
//#include "GameObject.h"
#include <iostream>
#include "Map.h"
//#include "EntityComponentSystem.h"
//#include "Components.h"
#include "EntityComponentSystem/Components.h"
#include "Vector2D.h"
#include "Collision.h"


Map* map;

SDL_Renderer* Game::renderer = nullptr;//we have it set to nullptr because we haven't initialized SDL yet
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0, 800, 640 };

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

bool Game::isRunning = false;

const char* mapFile = "assets/terrain_ss.png";

enum groupLabels : std::size_t //we can have up to 32 of these
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};


//lists of objects in the groups in our renderer
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

Game::Game()
{}
Game::~Game()
{}

void Game::initializeGame(const char* title, int x_position, int y_position, int width, int height, bool fullscreen)
{
	int fullscreen_detector = 0;//workaround to get bool fullscreen working in SDL_CreateWindow, same with if statement below
	if (fullscreen)//if fullscreen is true then flags equal SDL_WINDOW_FULLSCREEN
	{
		fullscreen_detector = SDL_WINDOW_FULLSCREEN;//basically if fullscreen is true then the window becomes fullscreen
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //IF THIS RETURNS 0 THEN THE SDL SYSTEMS HAVE BEEN PROPERLY INITIALIZED
	{
		std::cout << "Subsystems Initialized" << std::endl;

		window = SDL_CreateWindow(title, x_position, y_position, width, height, fullscreen_detector);
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);//*FIGURE OUT HOW THIS WORKS*//
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);//red,green,blue,black
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}

	//Don't need the below commented out code anymore thanks to TextureManager.cpp/.h
	//SDL_Surface* temporarySurface = IMG_Load("assets/testimage.png");//creates a value that loads the png file
	//playerTexture = SDL_CreateTextureFromSurface(renderer, temporarySurface);//uses the loaded png file and the renderer to create a texture
	//SDL_FreeSurface(temporarySurface);//frees up the memory

	//playerTexture = TextureManager::LoadTexture("assets/testimage.png", renderer);
	//player = new GameObject("assets/player.png", 0, 0);
	//boss = new GameObject("assets/boss.png", 100, 100);
	map = new Map();

	//Entity Component System Implementation

	//No longer needed due to AddTile() method
	//tile0.addComponent<TileComponent>(200, 200, 32, 32, 0); //water
	//tile1.addComponent<TileComponent>(250, 250, 32, 32, 1); //dirt
	//tile1.addComponent<ColliderComponent>("dirt");
	//tile2.addComponent<TileComponent>(150, 150, 32, 32, 2); //grass
	//tile2.addComponent<ColliderComponent>("grass");

	Map::LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(3);
	player.addComponent<SpriteComponent>("assets/player_animations.png", true);
	player.addComponent<keyboardController>();//allows us to control our player
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	

	//newPlayer.addComponent<PositionComponent>();//this will give us access to position variables
	//newPlayer.getComponent<PositionComponent>().setPosition(500, 500);

}

void Game::handleEvents()
{
	
	SDL_PollEvent(&event);
	switch (event.type)//switch statement to check the form of event happening, duh
	{
	case SDL_QUIT://event.SDL_QUIT means that you want to quit the event, dumbass
		isRunning = false;
		break;
	default://default case, if you don't know what that means at this point you should kill yourself Dylan Driscoll
		break;
	}
}

void Game::update()
{
	//player->Update();//updates the player
	//boss->Update();//updates the boss
	manager.refresh();
	manager.update();//will update all the entities which in turn will update all the components

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	//sorts out camera movement
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}




void Game::render()
{
	SDL_RenderClear(renderer);

	//map->DrawMap(); No longer needed

	//player->Render();
	//boss->Render();
	//manager.draw();//fixes bug where player sprite does not appear

	for (auto& t : tiles)
	{
		t->draw();// will draw each tile one after another
	}

	for (auto& p : players)
	{
		p->draw();// will draw each player one after another
	}

	for (auto& e : enemies)
	{
		e->draw();// will draw each enemy one after another
	}

	//Everything below has been replaced thanks to GameObject.cpp/.h
	//SDL_RenderCopy(renderer, playerTexture, NULL, &destinationRectangle);//copys the render so it can be used

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Clean" << std::endl;
}

void Game::AddTile(int sourceX, int sourceY, int xPosition, int yPosition)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(sourceX, sourceY, xPosition, yPosition, mapFile);//This is how we will add a tile
	tile.addGroup(groupMap);
}

