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

using namespace std;
// define the constants
#define WIDTH 80
#define HEIGHT 25

// define the variables
int foodX = 0, foodY = 0;
int score = 0;
int snakeSize = 1;
int snakeX[100], snakeY[100];
bool gameOver = false;

// declare the direction variables
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection direction;

// declare the functions
void gotoxy(int x, int y);
void setScreenSize();
void screenBorder();
void readInstructions();
void drawSnake();
void drawFood();
void drawGame();
void moveSnake();
void checkFood();
void checkSnake();
void checkGame();

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
    int y = HEIGHT / 2 - 2;
    while (getline(file, line))
    {
        int x = ((WIDTH / 2) - (line.length()/2)-1);
        gotoxy(x, y);
        cout << line;
        y++;
    }
    file.close();
    gotoxy(WIDTH / 2, y);
    // wait for the user to press a key
    // if the user presses the space bar, the game starts
    // if the user presses the escape key, the game quits
    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 32)
            {
                system("cls");
                screenBorder();
                // start the game
                break;
            }
            else if (ch == 27)
            {
                exit(0);
            }
        }
    }
}

// write a function to draw snake
void drawSnake()
{
    for (int i = 0; i < snakeSize; i++)
    {
        gotoxy(snakeX[i], snakeY[i]);
        cout << char(219);
    }
}

// write a function to draw food
void drawFood()
{
    gotoxy(foodX, foodY);
    cout << char(254);
}

// write a function to draw the game
void drawGame()
{
    // set the random seed
    srand(time(0));
    // set the food position
    foodX = (rand() % (WIDTH - 2)) + 1;
    foodY = (rand() % (HEIGHT - 2)) + 1;
    // set the snake position
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    // set the score
    score = 0;
    // set the snake size
    snakeSize = 1;
    // set the direction of the snake
    int direction = UP;
    // set the game status
    bool gameOver = false;
    // draw the snake and food
    drawSnake();
    drawFood();
}

// write a function to move the snake
// the snake moves in the direction of the arrow keys
void moveSnake() {
    
    gotoxy(WIDTH/2, HEIGHT-2);
    cout << direction;
    // if the game is not over
    if (!gameOver)
    {
        
        // if the snake is not moving
        if (direction == STOP)
        {
            // do nothing
        }
        // if the snake is moving left
        else if (direction == LEFT)
        {
            // move the snake to the left
            for (int i = snakeSize; i > 0; i--)
            {
                snakeX[i] = snakeX[(i - 1)];
                snakeY[i] = snakeY[(i - 1)];
            }
            snakeX[0]--;
        }
        // if the snake is moving right
        else if (direction == RIGHT)
        {
            // move the snake to the right
            for (int i = snakeSize; i > 0; i--)
            {
                snakeX[i] = snakeX[(i - 1)];
                snakeY[i] = snakeY[(i - 1)];
            }
            snakeX[0]++;
        }
        // if the snake is moving up
        else if (direction == UP)
        {
            // move the snake up
            for (int i = snakeSize; i > 0; i--)
            {
                snakeX[i] = snakeX[(i - 1)];
                snakeY[i] = snakeY[(i - 1)];
            }
            snakeY[0]--;
        }
        // if the snake is moving down
        else if (direction == DOWN)
        {
            // move the snake down
            for (int i = snakeSize; i > 0; i--)
            {
                snakeX[i] = snakeX[(i - 1)];
                snakeY[i] = snakeY[(i - 1)];
            }
            snakeY[0]++;
        }
        // check the snake
        checkSnake();
        // check the food
        checkFood();
        // check the game
        checkGame();
    }
}

// write a function to check the food
void checkFood()
{
    // check if the snake eats the food
    if (snakeX[0] == foodX && snakeY[0] == foodY)
    {
        // increase the score
        score++;
        // increase the snake size
        snakeSize++;
        // set the random seed
        srand(time(0));
        // set the food position
        foodX = (rand() % (WIDTH - 2)) + 1;
        foodY = (rand() % (HEIGHT - 2)) + 1;
        // draw the food
        drawFood();
    }
}

// write a function to check the snake
void checkSnake()
{
    // check if the snake hits the border
    // if the snake hits the border, snake appear on the opposite border
    if (snakeX[0] == 0)
    {
        snakeX[0] = WIDTH - 1;
    }
    else if (snakeX[0] == WIDTH - 1)
    {
        snakeX[0] = 0;
    }
    else if (snakeY[0] == 0)
    {
        snakeY[0] = HEIGHT - 1;
    }
    else if (snakeY[0] == HEIGHT - 1)
    {
        snakeY[0] = 0;
    }
    
    // check if the snake hits itself
    for (int i = 1; i < snakeSize; i++)
    {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
        {
            // set the game status
            gameOver = true;
        }
    }
}

// write a function to check the game
void checkGame()
{
    // check if the game is over
    if (gameOver)
    {
        system("cls");
        screenBorder();
        // display the game over screen
        gotoxy(WIDTH / 2 - 5, HEIGHT / 2 - 1);
        cout << "GAME OVER";
        gotoxy(WIDTH / 2 - 5, HEIGHT / 2);
        cout << "SCORE: " << score;
        // wait for the user to press a key
        // if the user presses the space bar, the game starts
        // if the user presses the escape key, the game quits
        while (true)
        {
            if (_kbhit())
            {
                char ch = _getch();
                if (ch == 32)
                {
                    system("cls");
                    screenBorder();
                    drawGame();
                    break;
                }
                else if (ch == 27)
                {
                    exit(0);
                }
            }
        }
    }
}

// write a function to check if direction key is pressed
void checkDirection()
{
    // if the game is not over
    if (!gameOver)
    {
        // if the user presses the left arrow key
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 75)
            {
                // if the snake is moving right, stop the snake
                if (direction == RIGHT)
                {
                    direction = STOP;
                }
                // if the snake is moving left, change the direction
                else if (direction == LEFT)
                {
                    direction = STOP;
                }
                // if the snake is moving up, change the direction
                else if (direction == UP)
                {
                    direction = LEFT;
                }
                // if the snake is moving down, change the direction
                else if (direction == DOWN)
                {
                    direction = LEFT;
                }
                // if the snake is not moving, change the direction
                else
                {
                    direction = LEFT;
                }
            }
            // if the user presses the right arrow key
            else if (ch == 77)
            {
                // if the snake is moving left, stop the snake
                if (direction == LEFT)
                {
                    direction = STOP;
                }
                // if the snake is moving right, change the direction
                else if (direction == RIGHT)
                {
                    direction = STOP;
                }
                // if the snake is moving up, change the direction
                else if (direction == UP)
                {
                    direction = RIGHT;
                }
                // if the snake is moving down, change the direction
                else if (direction == DOWN)
                {
                    direction = RIGHT;
                }
                // if the snake is not moving, change the direction
                else
                {
                    direction = RIGHT;
                }
            }
            // if the user presses the up arrow key
            else if (ch == 72)
            {
                // if the snake is moving down, stop the snake
                if (direction == DOWN)
                {
                    direction = STOP;
                }
                // if the snake is moving up, change the direction
                else if (direction == UP)
                {
                    direction = STOP;
                }
                // if the snake is moving left, change the direction
                else if (direction == LEFT)
                {
                    direction = UP;
                }
                // if the snake is moving right, change the direction
                else if (direction == RIGHT)
                {
                    direction = UP;
                }
                // if the snake is not moving, change the direction
                else
                {
                    direction = UP;
                }
            }
            // if the user presses the down arrow key
            else if (ch == 80)
            {
                // if the snake is moving up, stop the snake
                if (direction == UP)
                {
                    direction = STOP;
                }
                // if the snake is moving down, change the direction
                else if (direction == DOWN)
                {
                    direction = STOP;
                }
                // if the snake is moving left, change the direction
                else if (direction == LEFT)
                {
                    direction = DOWN;
                }
                // if the snake is moving right, change the direction
                else if (direction == RIGHT)
                {
                    direction = DOWN;
                }
                // if the snake is not moving, change the direction
                else
                {
                    direction = DOWN;
                }
            }
        }
    }
}

int main()
{
    // set the screen size
    setScreenSize();
    // set the screen border
    screenBorder();
    // fetch the text from instructions.txt
    readInstruction();
    // draw the game
    drawGame();
    // move the snake
    
    // set the direction of the snake
    int direction = 1;
    while (!gameOver)
    {
        // check the food
        checkFood();
        // check the direction
        checkDirection();
        // move the snake
        moveSnake();
        // check the game status
        checkGame();
        // delay the game
        Sleep(100);
        
    }
    getch();
}