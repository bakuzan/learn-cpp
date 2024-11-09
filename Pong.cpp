#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

enum eDirection
{
    NONE = 0,
    LEFT = 1,
    UPLEFT = 2,
    DOWNLEFT = 3,
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6
};

class cBall
{
private:
    int x, y;
    int originalX, originalY;
    eDirection direction;

public:
    cBall(int posX, int posY)
    {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = NONE;
    }
    void Reset()
    {
        x = originalX;
        y = originalY;
        direction = NONE;
    }
    void changeDirection(eDirection newDirection)
    {
        direction = newDirection;
    }
    void randomDirection()
    {
        direction = (eDirection)((rand() % 6) + 1);
    }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline eDirection getDirection() { return direction; }
    void Move()
    {
        switch (direction)
        {
        case NONE:
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UPLEFT:
            x--;
            y--;
            break;
        case DOWNLEFT:
            x--;
            y++;
            break;
        case UPRIGHT:
            x++;
            y--;
            break;
        case DOWNRIGHT:
            x++;
            y++;
            break;
        default:
            break;
        }
    }
    friend ostream &operator<<(ostream &o, cBall c)
    {
        o << "Ball[" << c.x << "," << c.y << "][" << c.direction << "]";
        return o;
    }
};

class cPaddle
{
private:
    int x, y;
    int originalX, originalY;

public:
    cPaddle()
    {
        x = y = 0;
    }
    cPaddle(int posX, int posY)
    {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }
    void Reset()
    {
        x = originalX;
        y = originalY;
    }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline void moveUp() { y--; }
    inline void moveDown() { y++; }
    friend ostream &operator<<(ostream &o, cPaddle c)
    {
        o << "Paddle[" << c.x << "," << c.y << "]";
        return o;
    }
};

class cGameManager
{
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cBall *ball;
    cPaddle *player1;
    cPaddle *player2;
    void ResetConsole()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);

        cursorInfo.dwSize = 100;
        cursorInfo.bVisible = FALSE;

        SetConsoleCursorInfo(hConsole, &cursorInfo);
        SetConsoleCursorPosition(hConsole, {0, 0});
    }

public:
    cGameManager(int w, int h)
    {
        srand(time(NULL));
        quit = false;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new cBall(w / 2, h / 2);
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w - 2, h / 2 - 3);
    }
    ~cGameManager()
    {
        delete ball, player1, player2;
    }
    void ScoreUp(cPaddle *player)
    {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }
    void Draw()
    {
        ResetConsole();

        // Top Wall
        for (int i = 0; i < width + 2; i++)
        {
            cout << "\xB2";
        }
        cout << endl;

        // Matrix to print out the map
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int ballX = ball->getX();
                int ballY = ball->getY();
                int player1X = player1->getX();
                int player1Y = player1->getY();
                int player2X = player2->getX();
                int player2Y = player2->getY();

                // Print out left wall
                if (j == 0)
                {
                    cout << '\xB2';
                }

                // Game position drawing...
                if (ballX == j && ballY == i)
                {
                    cout << "O";
                }
                else if (player1X == j && player1Y == i)
                {
                    cout << "\xDB";
                }
                else if (player1X == j && player1Y + 1 == i)
                {
                    cout << "\xDB";
                }
                else if (player1X == j && player1Y + 2 == i)
                {
                    cout << "\xDB";
                }
                else if (player1X == j && player1Y + 3 == i)
                {
                    cout << "\xDB";
                }
                else if (player2X == j && player2Y == i)
                {
                    cout << "\xDB";
                }
                else if (player2X == j && player2Y + 1 == i)
                {
                    cout << "\xDB";
                }
                else if (player2X == j && player2Y + 2 == i)
                {
                    cout << "\xDB";
                }
                else if (player2X == j && player2Y + 3 == i)
                {
                    cout << "\xDB";
                }
                else
                {
                    cout << " ";
                }

                // Print out right wall
                if (j == width - 1)
                {
                    cout << '\xB2';
                }
            }

            // Go to next line after finishing a row.
            cout << endl;
        }

        // Bottom Wall
        for (int i = 0; i < width + 2; i++)
        {
            cout << "\xB2";
        }
        cout << endl;

        cout << "Score 1: " << score1 << endl
             << "Score 2: " << score2 << endl;
    }
    void Input()
    {
        ball->Move();
        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();

        if (_kbhit())
        {
            char key = _getch();
            if (key == up1)
            {
                if (player1Y > 0)
                    player1->moveUp();
            }
            if (key == up2)
            {
                if (player2Y > 0)
                    player2->moveUp();
            }
            if (key == down1)
            {
                if (player1Y + 4 < height)
                    player1->moveDown();
            }
            if (key == down2)
            {
                if (player2Y + 4 < height)
                    player2->moveDown();
            }

            if (ball->getDirection() == NONE)
            {
                ball->randomDirection();
            }

            if (key == 'q')
            {
                quit = true;
            }
        }
    }
    void Logic()
    {
        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();

        // LEFT PADDLE
        for (int i = 0; i < 4; i++)
        {
            if (ballX == player1X + 1)
                if (ballY == player1Y + i)
                    ball->changeDirection((eDirection)((rand() % 3) + 4));
        }

        // RIGHT PADDLE
        for (int i = 0; i < 4; i++)
        {
            if (ballX == player2X - 1)
                if (ballY == player2Y + i)
                    ball->changeDirection((eDirection)((rand() % 3) + 1));
        }

        // BOTTOM WALL
        if (ballY == height - 1)
        {
            ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        }

        // TOP WALL
        if (ballY == 0)
        {
            ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        }

        // RIGHT WALL
        if (ballX == width - 1)
        {
            ScoreUp(player1);
        }
        // LEFT WALL
        if (ballX == 0)
        {
            ScoreUp(player2);
        }
    }
    void Run()
    {
        while (!quit)
        {
            Draw();
            Input();
            Logic();
            Sleep(1000 / 100); // Slow the game down
        }
    }
};

int main()
{
    cGameManager c(40, 20);
    c.Run();
    return 0;
}
