#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>
#include <thread>

using namespace std;

// screen constants
#define WIDTH 80
#define HEIGHT 25

// game variables
int score, snakeSize;
int foodX, foodY;
int snakeX[100], snakeY[100];
bool gameOver;
int tailX, tailY;
int gameDelay = 100;

// direction variables
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection direction;

// game functions
void gotoxy(int x, int y);
void setScreenSize();
void screenBorder();
void readInstructions();
void readControls();
void drawSnake();
void drawFood();
void drawScore();
void drawGame();
void moveSnake();
void checkFood();
void generateFood();
void checkSnake();
void checkGame();
void startGame();
void changeDirection();
void increaseSpeed();
void clrAndStartGame();

// gotoxy function
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// screen size is 80x30
// cursor is not visible
void setScreenSize()
{
    system("mode con cols=80 lines=30");
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// function to draw the screen border
void screenBorder()
{
    for (int i = 0; i < WIDTH; i++)
    {
        gotoxy(i, 0);
        cout << char(205);
        gotoxy(i, HEIGHT - 1);
        cout << char(205);
    }
    for (int i = 0; i < HEIGHT; i++)
    {
        gotoxy(0, i);
        cout << char(186);
        gotoxy(WIDTH - 1, i);
        cout << char(186);
    }
    gotoxy(0, 0);
    cout << char(201);
    gotoxy(0, HEIGHT - 1);
    cout << char(200);
    gotoxy(WIDTH - 1, 0);
    cout << char(187);
    gotoxy(WIDTH - 1, HEIGHT - 1);
    cout << char(188);
}

// function to fetch the multiline instruction from instructions.txt
// display it in the center of the screen
void readInstruction()
{
    ifstream file;
    file.open("instructions.txt");
    string line;
    int y = HEIGHT / 2;
    while (getline(file, line))
    {
        int x = ((WIDTH / 2) - (line.length() / 2) - 1);
        gotoxy(x, y);
        cout << line;
        y++;
    }
    file.close();
    gotoxy(WIDTH / 2, y);
    readControls();
    clrAndStartGame();
}

// function to read the controls instructions from controls.txt
// display it in the bottom of game area
void readControls()
{

    ifstream file;
    file.open("controls.txt");
    string line;
    int y = HEIGHT;
    while (getline(file, line))
    {
        int x = ((WIDTH / 2) - (line.length() / 2) - 1);
        gotoxy(x, y);
        cout << line;
        y++;
    }
    file.close();
    gotoxy(WIDTH / 2, y);
}

// function to draw snake
void drawSnake()
{
    for (int i = 0; i < snakeSize; i++)
    {
        gotoxy(snakeX[i], snakeY[i]);
        cout << '#';
    }
}

// write a function to draw food
// refresh the border since the upper left corner disappears
void drawFood()
{
    gotoxy(foodX, foodY);
    cout << char(254);
    screenBorder();
}

// function to display the score
void drawScore()
{
    gotoxy(WIDTH - 15, 0);
    cout << "Score: " << score;
}

// function to draw the game
void drawGame()
{
    readControls();
    drawSnake();
    drawFood();
    drawScore();
}

// function to move the snake according to the direction active
void moveSnake()
{
    tailX = snakeX[snakeSize - 1];
    tailY = snakeY[snakeSize - 1];
    changeDirection();
    for (int i = snakeSize - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
    if (direction == LEFT)
    {
        snakeX[0]--;
    }
    else if (direction == RIGHT)
    {
        snakeX[0]++;
    }
    else if (direction == UP)
    {
        snakeY[0]--;
    }
    else if (direction == DOWN)
    {
        snakeY[0]++;
    }
    drawSnake();
    gotoxy(tailX, tailY);
    cout << " ";
}

// function to change the direction of the snake when the user presses the arrow keys
void changeDirection()
{
    // detect the key pressed
    if (_kbhit())
    {
        char ch = _getch();
        if (ch == 'a' || ch == 'A')
        {
            if (direction != RIGHT)
            {
                direction = LEFT;
            }
        }
        else if (ch == 'd' || ch == 'D')
        {
            if (direction != LEFT)
            {
                direction = RIGHT;
            }
        }
        else if (ch == 'w' || ch == 'W')
        {
            if (direction != DOWN)
            {
                direction = UP;
            }
        }
        else if (ch == 's' || ch == 'S')
        {
            if (direction != UP)
            {
                direction = DOWN;
            }
        }
    }
}

// function to check if the snake eats the food
// if the snake eats the food:
// increase the score by 1
// increase the size of the snake by 1
// increase the speed
// generate a new food
void checkFood()
{
    if (snakeX[0] == foodX && snakeY[0] == foodY)
    {
        score++;
        snakeSize++;
        // increase the speed
        increaseSpeed();
        generateFood();
    }
}

// function to generate the food
// generate the food randomly
// if the snake eats the food, new food is generated
void generateFood()
{
    foodX = rand() % (WIDTH - 2) + 1;
    foodY = rand() % (HEIGHT - 2) + 1;
    drawFood();
}

// function to check if the snake hits the wall or itself
void checkSnake()
{
    // if the snake hits the wall, the snake passes through the wall and appear on the other side of the screen
    if (snakeX[0] == 0 || snakeX[0] == WIDTH - 1 || snakeY[0] == 0 || snakeY[0] == HEIGHT - 1)
    {
        if (snakeX[0] == 0)
        {
            snakeX[0] = WIDTH - 2;
        }
        else if (snakeX[0] == WIDTH - 1)
        {
            snakeX[0] = 1;
        }
        else if (snakeY[0] == 0)
        {
            snakeY[0] = HEIGHT - 2;
        }
        else if (snakeY[0] == HEIGHT - 1)
        {
            snakeY[0] = 1;
        }
        screenBorder();
        drawScore();
    }
    // if the snake hits itself, game is over
    for (int i = 1; i < snakeSize; i++)
    {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
        {
            gameOver = true;
        }
    }
}

// function to check if the game is over
void checkGame()
{
    // if the game is over
    if (gameOver)
    {
        system("cls");
        screenBorder();
        // display the game over message
        gotoxy(WIDTH/2-5, HEIGHT/2-3);
        cout << "Game Over!";
        // display the score over message
        gotoxy(WIDTH/2-4, HEIGHT/2-2);
        cout << "Score: " << score;
        readInstruction();
        clrAndStartGame();
    }
}

// function to clear the screen and start the game with keyboard press
// wait for the user to press a key
// if the user presses the space bar or key 'n', the game starts with gameDelay=200
// if the user presses the key 'h', the game starts with gameDelay=100
// if the user pressed the key 'e', the game starts with gameDelay=300
// if the user presses the escape key, the game quits
void clrAndStartGame()
{
    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 32 || ch == 'n')
            {
                system("cls");
                screenBorder();
                gameDelay = 200;
                break;
            }
            else if (ch == 'h')
            {
                system("cls");
                screenBorder();
                gameDelay = 100;
                break;
            }
            else if (ch == 'e')
            {
                system("cls");
                screenBorder();
                gameDelay = 300;
                break;
            }
            else if (ch == 27)
            {
                exit(0);
            }
        }
    }
    // start the game
    startGame();
}

// function to increase the speed of the game
// if the gameDelay is greather than 200, decrease the gameDelay by 8
// else if the gameDelay is greater than 100, decrease the gameDelay by 7
// else if the gameDelay is greater than 50, decrease the gameDelay by 4
// else if the gameDelay is greater than 40, decrease the gameDelay by 3
void increaseSpeed()
{
    if (gameDelay > 200)
    {
        gameDelay -= 8;
    }
    else if (gameDelay > 100)
    {
        gameDelay -= 7;
    }
    else if (gameDelay > 50)
    {
        gameDelay -= 4;
    }
    else if (gameDelay > 40)
    {
        gameDelay -=3;
    }
}

// function to control the game
void controlGame()
{
    // move the snake
    moveSnake();
    // check if the snake eats the food
    checkFood();
    // check if the snake hits the wall or itself
    checkSnake();
    // check if the game is over
    checkGame();
}

// write a function to start the game
void startGame()
{
    // set the starting direction
    direction = RIGHT;

    // set the starting position of the snake
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;

    // set the starting position of the food
    foodX = (rand() % (WIDTH - 2)) + 1;
    foodY = (rand() % (HEIGHT - 2)) + 1;

    // set the starting score
    score = 0;

    // set the starting size of the snake
    snakeSize = 1;

    // set the starting gameOver to false
    gameOver = false;

    // control the game
    while (!gameOver)
    {
        controlGame();

        // delay the game
        Sleep(gameDelay);

        // draw the game
        drawGame();
    }
}

int main()
{
    // set the screen size
    setScreenSize();

    // set the screen border
    screenBorder();

    // read the instructions
    readInstruction();

    // start the game
    startGame();

    getch();
}