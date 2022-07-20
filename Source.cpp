#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;//map dimensions
const int height = 20;
int x, y, fruitX, fruitY, score;//head ,fruit coordinates
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
void Setup() //starting game
{
    //start of the game
    gameOver = false;
    dir = STOP; //snake will not move untill we move it.
    x = width / 2;// the head of snake will be centered on the map.
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height; // the fruit will be randomed on the map
    score = 0;
}
void Draw() //drawing map , snake , fruits
{
    system("cls"); //system("clear");//clearing the console window screen to draw the map
    for (int i = 0; i < width + 2; i++)//drawin first line
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)//drawing body
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)//then we are in first row
                cout << "#";
            if (i == y && j == x)// if coordinates = snake head ,  print head
                cout << "O";
            else if (i == fruitY && j == fruitX)//if coordinates = fruit print fruit
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)//if we are at the position of the tail
                    {
                        cout << "o"; //cout the tail
                        print = true;
                    }
                }
                if (!print)//else print blank space to save the map formula
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)//drawing last line
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()  //getting controls pressed
{
    if (_kbhit())//checking if a key is pressed
    {
        switch (_getch()) // switch at whis key is pressed on keyboard
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic()  //moving snake and acting with fruits
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x; // first position is head position which is required to follow
        tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        //i=1 bec tailx[0] is taken already identified by us
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)//dealing with snake movement
    {
    case LEFT://if direction is left decrease x coordinate by 1 and so on.
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
    //if (x > width || x < 0 || y > height || y < 0)
    //  gameOver = true;
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)//this condition ends a game if the snake ate itself
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
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
        Sleep(10); //sleep(10);
    }
    return 0;
}