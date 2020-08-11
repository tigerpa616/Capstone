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

//Don't need the below commented out code anymore thanks to GameObject.cpp/.h
//SDL_Texture* playerTexture;//Creates a texture that will be used later to be a moving image
//SDL_Rect sourceRectangle, destinationRectangle;//allows us to determine position of the playerTexture

//GameObject* player;
//GameObject* boss;
Map* map;

SDL_Renderer* Game::renderer = nullptr;//we have it set to nullptr because we haven't initialized SDL yet
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t //we can have up to 32 of these
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

//No longer needed due to AddTile() method
//auto& tile0(manager.addEntity());
//auto& tile1(manager.addEntity());
//auto& tile2(manager.addEntity());

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

	Map::LoadMap("assets/pyxel_16x16.map", 16, 16);

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/player_idle.png", 4, 500);
	player.addComponent<keyboardController>();//allows us to control our player
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);

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
	
	//player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));

	//if (player.getComponent<TransformComponent>().position.x > 100)
	//{
		//player.getComponent<SpriteComponent>().setTexture("assets/boss.png"); //swaps the sprites
	//}


	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
		
	}
}

//lists of objects in the groups in our renderer
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));


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

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);//This is how we will add a tile
	tile.addGroup(groupMap);
}

