#include <algorithm>
#include <conio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>

using namespace std;
class qpzxship
{
public:
    int x, y;
    qpzxship(int width, int height)
    {
        x = width / 2;
        y = height;
    }
};

class qpzxgame
{
private:
    int height;
    int width;
    int score = -20;
    bool quit;
    qpzxship *ship;
    bool **asteriods;

public:
    qpzxgame(int w, int h)
    {
        height = h;
        width = w;
        quit = false;
        ship = new qpzxship(width, height);

        asteriods = new bool *[h];
        for (int i = 0; i < h; i++)
        {
            asteriods[i] = new bool[w];
        }
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                asteriods[j][i] = 0;
            }
        }
    }
    void move()
    {
        for (int i = 0; i < width; i++)
        {
            if (rand() % 10 == 1)
                asteriods[i][0] = true;
            else
                asteriods[i][0] = false;
        }
        for (int i = height - 1; i > 0; i--)
        {
            for (int j = 0; j < width; j++)
            {

                asteriods[j][i] = asteriods[j][i - 1];
            }
        }
    }
    void draw()
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (j == 0 || j == width - 1)
                    cout << "*";
                else if (asteriods[j][i] == true)
                    cout << "@";
                else if (j == ship->x && i == (ship->y) - 1)
                    cout << "^";
                else
                    cout << " ";
            }
            cout << endl;
        }
        cout << "score:" << score << endl;
    }
    void input()
    {
        if (kbhit)
        {
            char ch = getch();
            if (ch == 'a')
                ship->x--;
            if (ch == 'd')
                ship->x++;
            if (ch == 'q')
                quit = true;
        }
    }
    void logic()
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (asteriods[j][i] == true && j == ship->x && i == (ship->y) - 1)
                    quit = true;
                if (ship->x == 0 || ship->x == width - 1)
                    quit = true;
            }
        }
        score++;
        // Beep(523,500);
        cout << "\x07";
    }
    void run()
    {
        while (!quit)
        {
            draw();
            input();
            move();
            logic();
        }
    }
};

int main()
{
    srand(time(NULL));
    qpzxship shipobj(20, 20);
    qpzxgame gameobj(20, 20);

    gameobj.run();
    return 0;
}