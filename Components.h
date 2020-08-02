#pragma once
#include "EntityComponentSystem.h"

class PositionComponent : public Component
{
private: 
	int xposition;
	int yposition;

public: 
	//we have to expose and set our x and y positions
	int x() { return xposition; }
	int y() { return yposition; }

	void initialize() override
	{
		xposition = 0;
		yposition = 0;
	}

	void update() override
	{
		xposition++;
		yposition++;
	}

	void setPosition(int x, int y)
	{
		xposition = x;
		yposition = y;
	}
};