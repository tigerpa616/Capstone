#include "BattleSystem.h"


BattleSystem::BattleSystem()
{
	//Turn-Based Combat System
	std::cout << "testing turn based combat" << std::endl;
}

void BattleSystem::defeat()
{
	std::cout << "you lost the battle" << std::endl;
	health = 20;
	magic = 20;
	enemyHealth = 35;
}

void BattleSystem::victory()
{
	std::cout << "you succeded in battle" << std::endl;
	health = 20;
	magic = 20;
	enemyHealth = 35;
}