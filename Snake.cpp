#include <iostream>
#include <conio.h>
using namespace std;

#pragma region Globals

enum Movement
{
    NONE = 0,
    UP,
    RIGHT,
    DOWN,
    LEFT
};

bool gameOver;
const int width = 20;
const int height = 20;
int snakeX, snakeY, foodX, foodY, score;
Movement movement;

#pragma endregion

#pragma region Helpers

void PlaceFood()
{
    foodX = rand() % width;
    foodY = rand() % height;
}

#pragma endregion

void Setup()
{
    gameOver = false;
    movement = Movement::NONE;

    // Place snake in the middle
    snakeX = width / 2;
    snakeY = height / 2;

    // Place initial target randomly
    PlaceFood();
}

void Draw()
{
    system("cls"); // Clear terminal...duhh!

    // Top Wall
    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }

    cout << endl;

    // Matrix to print out the map
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Print out wall
            if (j == 0)
            {
                cout << '#';
            }

            // Print other things
            if (i == snakeY && j == snakeX)
            {
                cout << 'O';
            }
            else if (i == foodY && j == foodX)
            {
                cout << 'X';
            }
            else
            {
                cout << ' ';
            }

            // Print out wall
            if (j == width - 1)
            {
                cout << '#';
            }
        }

        // Go to next line after finishing a row.
        cout << endl;
    }

    // Bottom Wall
    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }

    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            movement = Movement::UP;
            break;
        case 'a':
            movement = Movement::LEFT;
            break;
        case 's':
            movement = Movement::DOWN;
            break;
        case 'd':
            movement = Movement::RIGHT;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    switch (movement)
    {
    case Movement::UP:
        snakeY--;
        break;
    case Movement::RIGHT:
        snakeX++;
        break;
    case Movement::DOWN:
        snakeY++;
        break;
    case Movement::LEFT:
        snakeX--;
        break;
    }

    // Hit the wall, game over
    if (snakeX > width || snakeX < 0 || snakeY > height || snakeY < 0)
    {
        gameOver = true;
    }

    // Eat the food
    if (snakeX == foodX && snakeY == foodY)
    {
        score += 10;
        PlaceFood();
    }
}

int main()
{
    Setup();

    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        // Sleep(10);
    }

    return 0;
}