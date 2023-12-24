#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameOver;
const int width = 20, height = 20;  // play area
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
// key map
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	// starts at the middle
	x = width / 2;
	y = height / 2;
	// place fruit randomly
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");
	
	// top border
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// left border
			if (j == 0)
				cout << "#";
			// mouth at the current x, y
			if (i == y && j == x)
				cout << "O";
			// check mouth and fruit at the same position
			else if (i == fruitY && j == fruitX)
				cout << "F";
			// print the tail
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
					
				}
				if (!print)
					cout << " ";
			}
			// right border
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	// bottom border
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	// print the current score
	cout << endl;
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()
{
	// map the keybord map. a, d, w, s and arrows support
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 75:
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 77:
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 72:
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 80:
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	// all tail position logic 
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	// mouth and current position
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	
	// game over when hitting walls
	//if (x > width || x < 0 || y > height || y < 0)
	//	gameOver = true;
	// respawn at the other end
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	// game over when hitting the body of the sanke
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	
	// logic if snake eats the fruit
	if (x == fruitX && y == fruitY)
	{
		nTail++;
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
}

int main()
{
	Setup();
	// loop untill the game over
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50); // slows the game
	}
	return 0;
}