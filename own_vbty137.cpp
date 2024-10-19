#include <conio.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;
#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77

class vbtyball
{
public:
    int x, y;
    bool rightjump = false, leftjump = false;
    bool empty = false;
    vbtyball(int width, int height) // set the values for the ball,constructor
    {
        x = 0;
        y = (height / 2) + 1;
        empty = false;
        rightjump = false;
        leftjump = false;
    }
};

class vbtygame
{
private:
    int height;
    int width;
    int quit = false;
    int score = 0;

    vbtyball *ball; // pointer to our vbtyball constructor
    bool **map;     // a bool matrix

public:
    vbtygame(int w, int h)
    {
        height = h;
        width = w;
        ball = new vbtyball(width, height); // parameterized constructor

        map = new bool *[h]; // initialise data to the matrix
        for (int i = 0; i < h; i++)
        {
            map[i] = new bool[w];
        }
        for (int i = 0; i < width; i++) // make all matrix elements false
        {
            for (int j = 0; j < height; j++)
            {
                map[j][i] = false;
            }
        }
        map[0][(height / 2) + 2] = true; // make the element below ball as true
    }
    ~vbtygame()
    {
        delete ball;
        delete map;
    }

    void move() // methods
    {
        for (int i = 0; i < width; i++)
        {
            if (rand() % 15 != 1)
                map[i][width] = false;
            else // put true in two consecutive columns so that we can get ##
            {
                map[i][width] = true;
                map[i][width - 1] = true;
            }
        }
        for (int i = 0; i < width; i++) // move the columns from right to left
        {
            for (int j = 1; j < height; j++)
            {
                map[i][j] = map[i][j + 1];
                if (j == 0 && i == ((height / 2) + 2)) // below block
                    map[i][j] = true;
            }
        }
    }
    void jump() // if rightjump or leftjump is pressed move the ball according to the below instructions
    {
        if (ball->rightjump == true)
        {
            if (map[(ball->y) - 1][(ball->x) + 1] == false)
            {
                (ball->x)++; // right jump button pressed
                (ball->y)--;
                score++;
                move();
                draw();
                Sleep(500);
                if (map[(ball->y) - 1][(ball->x) + 1] == false)
                {
                    (ball->x)++;
                    (ball->y)--;
                    score++;
                    move();
                    draw();
                    Sleep(500);
                    if (map[(ball->y) - 1][(ball->x) + 1] == false)
                    {
                        (ball->x)++;
                        (ball->y)--;
                        score++;
                        move();
                        draw();
                        Sleep(500);
                        if (map[(ball->y) + 1][(ball->x) + 1] == false)
                        {
                            (ball->x)++;
                            (ball->y)++;
                            score++;
                            move();
                            draw();
                            Sleep(500);
                            // if(map[(ball->y)+1][(ball->x)+1]==false)
                            //    {
                            //      (ball->x)++;
                            //       (ball->y)++;
                            //        draw();

                            //     }
                        }
                    }
                }
            }
            ball->rightjump = false;
        }
        else
        {
            if (ball->leftjump == true)
            {
                if (map[(ball->y) - 1][(ball->x) - 1] == false)
                {
                    (ball->x)--; // left jump button pressed
                    (ball->y)--;
                    score++;
                    move();
                    draw();
                    Sleep(500);
                    if (map[(ball->y) - 1][(ball->x) - 1] == false)
                    {
                        (ball->x)--;
                        (ball->y)--;
                        score++;
                        move();
                        draw();
                        Sleep(500);
                        if (map[(ball->y) - 1][(ball->x) - 1] == false)
                        {
                            (ball->x)--;
                            (ball->y)--;
                            score++;
                            move();
                            draw();
                            Sleep(500);
                            if (map[(ball->y) - 1][(ball->x) + 1] == false)
                            {
                                (ball->x)--;
                                (ball->y)++;
                                score++;
                                move();
                                draw();
                                Sleep(500);
                                // if(map[(ball->y)-1][(ball->x)+1]==false)
                                //    {
                                //      (ball->x)--;
                                //      (ball->y)++;
                                //      draw();
                                //    }
                            }
                        }
                    }
                }
            }
            ball->leftjump = false;
        }
    }
    void fall() // if below the ball is false decrease the the ball's height
    {
        int row = ball->y;
        int col = ball->x;
        while (map[row + 1][col] != true && row < height - 2)
        {
            (ball->y)++;
            row++;
            move();
            draw();
            Sleep(500);
        }
    }
    void logic()
    {
        if ((ball->x) >= width) // if ball reaches to the right increase score and move ball to its initial position
        {
            ball->x = 0;
            ball->y = (height / 2) + 1;
            score = score + 25;
            draw();
            Sleep(300);
            //    map[(height / 2) + 2][0] = true
        }
        if ((ball->x) < 0)
        {
            ball->x = 0;
            ball->y = (height / 2) + 1;
            score = score - 5;
            draw();
        }
        if ((ball->y) >= (height - 2))
        {
            cout << "your score is :" << score << endl;
            Sleep(1000);
            exit(1);
        }
    }
    void input()
    {
        if (kbhit) // if key is pressed take inputs
        {
            char ch = getch();
            if (ch == 's') // stay at the same place
            {
            }
            if (ch == 'a')
            {
                ball->x = (ball->x) - 2;
                score++;
                move();
                draw();
                Sleep(500);
            }
            if (ch == 'd')
            {
                ball->x++;
                score++;
                move();
                draw();
                Sleep(500);
            }
            if (ch == 'w')
            {
                if (map[(ball->y) - 1][ball->x] == false)
                {
                    ball->y--;
                    if ((ball->x) != 0)
                        score++;
                    move();
                    draw();
                    Sleep(300);
                    if (map[(ball->y) - 1][ball->x] == false)
                    {
                        ball->y--;
                        if ((ball->x) != 0)
                            score++;
                        move();
                        draw();
                        Sleep(300);
                    }
                }
            }
            //  if (ch == 's')
            //      ball->y++;
            if (ch == 'v')
                ball->rightjump = true;
            if (ch == 'b')
                ball->leftjump = true;
            if (ch == 'q')
                quit = true;
        }
        else
        {
        }
    }
    void draw()
    {
        system("cls");
        cout << "\033[2J\033[1;1H"; // special character string that  clears the string
        // cout << ball->x << " " << ball->y << endl;    //coordinates
        // cout<<(ball->y)+1<<endl;
        // cout<<map[ball->x][(ball->y)+1]<<endl;
        cout << endl;
        cout << "_____________" << "VBTY Ground" << "_____________" << endl;
        cout << "move your ball and try to cross the ground" << endl;
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (j == 0 && i == ((height / 2) + 2)) // below block
                    map[i][j] = true;
                if (j == ball->x && i == ball->y) // print ball
                    cout << "O";
                else if (i == 0 || i == height - 1) // print upper and lower ball
                    cout << "#";
                //   else if(j==0 && i==(height/2)+2)
                //     cout<<"##";
                else if (map[i][j] == true) // print the blocks
                    cout << "#";
                else
                    cout << " ";
            }
            cout << endl;
        }
        cout << "score:" << score << endl;
        cout << "Press a to move left,d for right, w for jump, v for right jump, b for left jump" << endl;
        int xc = ball->x; // col
        int yc = ball->y; // row

        if (map[yc + 1][xc] == true)
            cout << "present" << endl;
        else
            cout << "absent" << endl;
    }
    void run()
    {
        while (!quit)
        {
            draw();
            Sleep(200);
            logic();
            input();
            logic();
            if (ball->rightjump == true)
                jump();
            if (ball->leftjump == true)
                jump();
            fall();
            draw();
            Sleep(300);
            move();
        }
    }
};

int main()
{
    srand(time(NULL));
    vbtygame gameobj(20, 20);
    vbtyball ballobj(20, 20);

    gameobj.run();
    getchar();
    return 0;
}