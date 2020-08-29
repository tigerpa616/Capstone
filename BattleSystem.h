#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

class BattleSystem
{
public:
	int health, magic = 20;
	int enemyHealth = 35;
	int move;

	BattleSystem();
	void defeat();
	void victory();
};