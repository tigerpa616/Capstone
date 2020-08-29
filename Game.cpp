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
#include "AssetManager.h"


Map* map;

SDL_Renderer* Game::renderer = nullptr;//we have it set to nullptr because we haven't initialized SDL yet
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0, 800, 640 };

Manager manager;
auto& player(manager.addEntity());


bool Game::isRunning = false;

AssetManager* Game::assets = new AssetManager(&manager);



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
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//red,green,blue,black
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}

	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/player_animations.png"); //for some reason this doesn't work?
	
	map = new Map("terrain", 3, 32);
	
	//Entity Component System Implementation

	map->LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(800.0f, 640.0f, 32, 32, 4);
	player.addComponent<SpriteComponent>("assets/player_animations.png", true);
	player.addComponent<keyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
}

//lists of objects in the groups in our renderer
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
//auto& enemies(manager.getGroup(groupEnemies));

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
	SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPosition = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();//will update all the entities which in turn will update all the components

	for (auto& c : colliders)
	{
		SDL_Rect cCollider = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCollider, playerCollider))
		{
			player.getComponent<TransformComponent>().position = playerPosition;
		}
	}

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

	for (auto& c : colliders)
	{
		c->draw();// will draw each collider one after another
	}

	for (auto& p : players)
	{
		p->draw();// will draw each player one after another
	}

	//for (auto& e : enemies)
	//{
		//e->draw();// will draw each enemy one after another
	//}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Clean" << std::endl;
}


