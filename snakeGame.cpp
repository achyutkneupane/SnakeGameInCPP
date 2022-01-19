// write a snake game in c++

// The snake is to be controlled by the arrow keys.
// The snake can eat the food.
// The snake can die if it hits itself.
// The snake appears in opposite direction after it hits the wall.
// The window size is 800x600.
// The starting screen is shown with the text from instructions.txt
// The text is written in center of the screen.

// User can start the game by pressing the space bar.
// User can restart the game after dying by pressing the space bar.
// User can quit the game by pressing the escape key.

// import the libraries
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
// define the constants
#define WIDTH 80
#define HEIGHT 25

// define the variables
int score, snakeSize;
int foodX, foodY;
int bonusFoodX, bonusFoodY;
int snakeX[100], snakeY[100];
bool gameOver;
int tailX, tailY;
int gameDelay = 100;

// declare the direction variables
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection direction;

// declare the functions
void gotoxy(int x, int y);
void setScreenSize();
void screenBorder();
void readInstructions();
void readControls();
void drawSnake();
void drawFood();
void drawBonusFood();
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

// define the gotoxy function
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// set the screen size to 80x25
void setScreenSize()
{
    system("mode con cols=80 lines=30");
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// define the screen border
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

// fetch the multiline instruction from instructions.txt and display it vertically and horizontally center of the screen
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

// read the controls instructions from controls.txt
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

// write a function to draw snake
// clear the previous path of the snake
// draw the snake
void drawSnake()
{
    for (int i = 0; i < snakeSize; i++)
    {
        gotoxy(snakeX[i], snakeY[i]);
        cout << char(219);
    }
}

// write a function to draw food
// the food is represented by an '*'
void drawFood()
{
    gotoxy(foodX, foodY);
    cout << char(254);
    screenBorder();
}

// write a function to display the score
void drawScore()
{
    gotoxy(WIDTH - 15, 0);
    cout << "Score: " << score;
}

// write a function to display the game
void drawGame()
{
    readControls();
    drawSnake();
    drawFood();
    drawScore();
}

// write a function to move the snake when the user presses the arrow keys
void moveSnake()
{
    tailX = snakeX[snakeSize - 1];
    tailY = snakeY[snakeSize - 1];
    changeDirection();
    // move the snake in the direction of the key pressed
    for (int i = snakeSize - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
    // move the snake in the direction of the key pressed
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

// write a function to change the direction of the snake when the user presses the arrow keys
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

// write a function to check if the snake eats the food
// if the snake eats the food
// increase the score by 1
// increase the size of the snake by 1
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

// write a function to generate the food
// generate the food randomly
// check if the food is on the snake
// if the food is on the snake
// generate the food randomly
void generateFood()
{
    foodX = rand() % (WIDTH - 2) + 1;
    foodY = rand() % (HEIGHT - 2) + 1;
    for (int i = 0; i < snakeSize; i++)
    {
        if (snakeX[i] == foodX && snakeY[i] == foodY)
        {
            generateFood();
        }
    }
}

// write a function to check if the snake hits the wall or itself
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
    // if the snake hits itself
    for (int i = 1; i < snakeSize; i++)
    {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
        {
            gameOver = true;
        }
    }
}

// write a function to check if the game is over
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
        gotoxy(WIDTH/2-4, HEIGHT/2-2);
        cout << "Score: " << score;
        readInstruction();
        clrAndStartGame();
    }
}

// write a function to clear the screen and start the game with keyboard press
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
    startGame();
}

// write a function to increase the speed of the game
// if the gameDelay is greather than 200, decrease the gameDelay by 3
// else if the gameDelay is greater than 100, decrease the gameDelay by 2
// else if the gameDelay is greater than 50, decrease the gameDelay by 1
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
    else if (gameDelay > 30)
    {
        gameDelay -=3;
    }
}

// write a function to control the game
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
    // // increase the speed of the game
    // increaseSpeed();
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
    // set the starting position of the bonus food
    bonusFoodX = (rand() % (WIDTH - 2)) + 1;
    bonusFoodY = (rand() % (HEIGHT - 2)) + 1;

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