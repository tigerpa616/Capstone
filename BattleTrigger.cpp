#include "BattleTrigger.h"

BattleTrigger::BattleTrigger(int playerMovement)
{
	if (playerMovement >= 20)
	{
		//initiate combat
		BattleSystem(); //start combat
	}
	
}
