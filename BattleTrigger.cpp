#include "BattleTrigger.h"

BattleTrigger::BattleTrigger(int playerMovement)
{
	if (playerMovement >= 5)
	{
		//initiate combat
		BattleSystem(); //start combat
	}
	
}
