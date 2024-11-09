#include <iostream>
#include <conio.h>
#include <windows.h>
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
int tailX[100], tailY[100];
int tailLength;
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
    // Clear screen
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});

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
                bool printTail = false;
                for (int k = 0; k < tailLength; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        printTail = true;
                    }
                }

                if (!printTail)
                {
                    cout << ' ';
                }
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
    // Update snake tail positions
    int prevTailX = tailX[0];
    int prevTailY = tailY[0];
    int prevTail2X, prevTail2Y;

    tailX[0] = snakeX;
    tailY[0] = snakeY;

    for (int i = 1; i < tailLength; i++)
    {
        prevTail2X = tailX[i];
        prevTail2Y = tailY[i];
        tailX[i] = prevTailX;
        tailY[i] = prevTailY;
        prevTailX = prevTail2X;
        prevTailY = prevTail2Y;
    }

    // Shift snake direction
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
    // if (snakeX > width || snakeX < 0 || snakeY > height || snakeY < 0)
    // {
    //     gameOver = true;
    // }

    // Hit the wall, come out the other side
    if (snakeX >= width)
        snakeX = 0;
    else if (snakeX < 0)
        snakeX = width - 1;
    if (snakeY >= height)
        snakeY = 0;
    else if (snakeY < 0)
        snakeY = height - 1;

    // Hit yourself, game over
    for (int i = 0; i < tailLength; i++)
    {
        if (tailX[i] == snakeX && tailY[i] == snakeY)
        {
            gameOver = true;
        }
    }

    // Eat the food
    if (snakeX == foodX && snakeY == foodY)
    {
        score += 10;
        PlaceFood();
        tailLength++;
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
        Sleep(1000 / 10); // Slow the refresh rate n times per second
    }

    return 0;
}