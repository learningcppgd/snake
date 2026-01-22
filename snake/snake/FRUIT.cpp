#include "FRUIT.h"
#include "raylib.h"


FRUIT::FRUIT(int x, int y)
	:x{ x }, y{ y } {
}

void FRUIT::drawFruit(int cellsize, Color col)
{
	DrawRectangle(x * cellsize, y * cellsize, cellsize, cellsize, col);
}
