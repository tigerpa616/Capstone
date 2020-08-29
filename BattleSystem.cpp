#include "BattleSystem.h"


BattleSystem::BattleSystem()
{
	//Turn-Based Combat System

	std::cout << "enemy hp: " << enemyHealth << std::endl << "hp: " << health << std::endl << "mp: " << magic << std::endl << "(1) Attack" << std::endl;
	std::cin >> move;

	if (move == 1)
	{
		enemyHealth -= 1;
		if (enemyHealth < 0)
		{
			victory();
		}

		if (health < 0)
		{
			defeat();
		}
		health -= 2;
	}

	if (move == 2)
	{
		//insta leave
	}
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