#pragma once

struct Animation
{
	int index;
	int frames;
	int speed;

	Animation() {} //default constructor that we are not gonna use
	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
	}
};