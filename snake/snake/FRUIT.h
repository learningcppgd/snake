#include "raylib.h"

#pragma once

class FRUIT
{
private:
	int x;
	int y;
public:
	FRUIT(int x, int y);
	~FRUIT();

	void drawFruit(int cellsize, Color col);
};

