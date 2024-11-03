#include <iostream>
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

void Setup()
{
    gameOver = false;
    movement = Movement::NONE;

    // Place snake in the middle
    snakeX = width / 2;
    snakeY = height / 2;

    // Place initial target randomly
    foodX = rand() % width;
    foodY = rand() % height;
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

            cout << ' ';

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
}

void Input()
{
}

void Logic()
{
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