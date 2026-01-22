#include <iostream>
#include "raylib.h"
#include <deque>
#include <raymath.h>

//constants
const int SCREENWIDTHEIGHT{ 800 };
// 20 x 20
const int cell_size{ SCREENWIDTHEIGHT / 20 };
const Color dark_gray{ DARKGRAY };
const Color red{ RED };
const Color green{ GREEN };

//function prototypes
void drawGrid();
bool eventTriggered(double interval);

double lastupdate_time{ 0 };


//classes, structs
struct Fruit
{
	Vector2 fruit_pos;

	Fruit()
	{
		fruit_pos = GenerateRandomPos();
	}
	~Fruit() {};

	void drawFruit()
	{
		DrawRectangle(int (fruit_pos.x) * cell_size, int (fruit_pos.y) * cell_size, cell_size, cell_size, red);
	}

	Vector2 GenerateRandomPos()
	{
		// there is 20x20 grid so we need values from 0 - 19
		float x = GetRandomValue(0, 19);
		float y = GetRandomValue(0, 19);
		return Vector2{ x,y };
	}
};


class Snake
{
public:
	std::deque<Vector2> body = { Vector2{1,1}, Vector2{1,2}, Vector2{1,3}};
	Vector2 direction{ 0,1 };

public:
	void drawSnakeBody()
	{
		for (size_t i{ 0 }; i < body.size(); i++)
		{
			DrawRectangle(int(body[i].x) * cell_size, int(body[i].y) * cell_size, cell_size, cell_size, green);
		}
	}

	void Update()
	{
		body.pop_front();
		body.push_back(Vector2Add(body[body.size() - 1], direction));
	}
};

int main()
{
	InitWindow(SCREENWIDTHEIGHT, SCREENWIDTHEIGHT, "SNAKE");
	SetTargetFPS(60);

	Fruit apple = Fruit();
	Snake snake = Snake();
	
	while (!WindowShouldClose())
	{

		BeginDrawing();
		{
			if (eventTriggered(0.2))
			{
				snake.Update();
			}

			if (IsKeyPressed(KEY_D) &&
				((snake.body.back().x + 1) != snake.body[snake.body.size() - 2].x))
			{
				snake.direction = { 1,0 };
			}
			else if (IsKeyPressed(KEY_A) &&
				((snake.body.back().x - 1) != snake.body[snake.body.size() - 2].x))
			{
				snake.direction = { -1,0 };
			}
			else if (IsKeyPressed(KEY_W) &&
				((snake.body.back().y - 1) != snake.body[snake.body.size() - 2].y))
			{
				snake.direction = { 0, -1 };
			}
			else if (IsKeyPressed(KEY_S) &&
				((snake.body.back().y + 1) != snake.body[snake.body.size() - 2].y))
			{
				snake.direction = { 0,1 };
			}
			ClearBackground(BLACK);
			drawGrid();
			apple.drawFruit();
			snake.drawSnakeBody();
		}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void drawGrid()
{
	for (int i{ 0 }; i < 20; i++)
	{
		DrawLine(0, i * cell_size, SCREENWIDTHEIGHT, i * cell_size, dark_gray);
		DrawLine(i * cell_size, 0 , i * cell_size, SCREENWIDTHEIGHT, dark_gray);
	}
}

bool eventTriggered(double interval)
{
	double current_time = GetTime();
	if (current_time - lastupdate_time >= interval)
	{
		lastupdate_time = current_time;
		return true;
	}
	return false;
}