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
    system("mode con cols=80 lines=25");
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
                break;
            }
            else if (ch == 27)
            {
                exit(0);
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
    getch();
}