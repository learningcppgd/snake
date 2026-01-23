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
bool AreVectorsEqual(Vector2 v1, Vector2 v2);

double lastupdate_time{ 0 };
int count{ 0 };

//classes, structs
struct Fruit
{
	Vector2 fruit_pos;

	Fruit()
	{
		fruit_pos = GenerateRandomPos();
	}

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
	bool grow{ false };

public:
	void drawSnakeBody()
	{
		for (size_t i{ 0 }; i < body.size(); i++)
		{
			DrawRectangle(int(body[i].x) * cell_size, int(body[i].y) * cell_size, cell_size, cell_size, green);
		}
	}

	void addTofront(Vector2 pos)
	{
		body.push_front(pos);
	}

	void Update()
	{
		if (!grow)
			body.pop_front();
		else
			grow = false;     

		body.push_back(Vector2Add(body.back(), direction));
	}

};

class Game
{
public:
	Snake snake;
	Fruit apple;

	void draw()
	{
		snake.drawSnakeBody();
		apple.drawFruit();
		drawGrid();
	}

	void Update() {
		snake.Update();
		CheckCollisionWithFruit();
		CheckCollisionWithTail();
	}

	void CheckCollisionWithFruit() {
		if (AreVectorsEqual(snake.body.back(), apple.fruit_pos)) {
			snake.grow = true;
			apple.fruit_pos = apple.GenerateRandomPos();
		}
	}

	void CheckCollisionWithTail() {
		for (size_t i = 0; i < snake.body.size() - 1; i++) {
			if (AreVectorsEqual(snake.body.back(), snake.body[i])) {
				std::cout << "Snake bit itself!\n";
			}
		}
	}
};


int main()
{
	InitWindow(SCREENWIDTHEIGHT, SCREENWIDTHEIGHT, "SNAKE");
	SetTargetFPS(60);

	Game game;
	
	while (!WindowShouldClose())
	{

		if (eventTriggered(0.2))
		{
			game.Update();
		}

		if (IsKeyPressed(KEY_D) &&
			((game.snake.body.back().x + 1) != game.snake.body[game.snake.body.size() - 2].x))
		{
			game.snake.direction = { 1,0 };
		}
		else if (IsKeyPressed(KEY_A) &&
			((game.snake.body.back().x - 1) != game.snake.body[game.snake.body.size() - 2].x))
		{
			game.snake.direction = { -1,0 };
		}
		else if (IsKeyPressed(KEY_W) &&
			((game.snake.body.back().y - 1) != game.snake.body[game.snake.body.size() - 2].y))
		{
			game.snake.direction = { 0, -1 };
		}
		else if (IsKeyPressed(KEY_S) &&
			((game.snake.body.back().y + 1) != game.snake.body[game.snake.body.size() - 2].y))
		{
			game.snake.direction = { 0,1 };
		}

		BeginDrawing();
		ClearBackground(BLACK);
		game.draw();
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

bool AreVectorsEqual(Vector2 v1, Vector2 v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}