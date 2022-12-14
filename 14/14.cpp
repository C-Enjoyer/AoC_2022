// 14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_POINTS  100
#define MAX_LINES   1000
#define MAX_X       1000
#define MAX_Y       1000

typedef enum ele
{
    AIR = 0,
    ROCK,
    SAND,

    ELE_MAX
} ele_t;

typedef struct point
{
    int x, y;
} point_t;

typedef struct line
{
    point_t p[MAX_POINTS];
    uint32_t pNum;
} line_t;

bool dropSand2(point_t p);
ele_t getGrid2(int x, int y);
bool dropSand(point_t p);
void parsePt(point_t* p, string s);
void drawLine(point_t p1, point_t p2);
void printGrid(void);

line_t lines[MAX_LINES] = { 0 };
uint32_t linesNum = 0;

int xMax = 0;
int yMax = 0;
int xMin = INT_MAX;
int yMin = INT_MAX;

ele_t grid[MAX_X][MAX_Y] = { AIR };

point sandDrop = { 500, 0 };

int main()
{
    while (1)
    {
        string inLine;
        getline(cin, inLine);

        if (inLine.length())
        {
            inLine.erase(remove(inLine.begin(), inLine.end(), ' '), inLine.end());
            inLine.erase(remove(inLine.begin(), inLine.end(), '-'), inLine.end());

            uint32_t fNum = 0;
            for (uint32_t i = 0; i < inLine.length(); i++)
            {
                if (inLine[i] == '>')
                {
                    parsePt(&lines[linesNum].p[lines[linesNum].pNum], inLine.substr(fNum, i - fNum));
                    lines[linesNum].pNum++;
                    fNum = i + 1;
                }
            }

            parsePt(&lines[linesNum].p[lines[linesNum].pNum], inLine.substr(fNum, inLine.length() - fNum));
            lines[linesNum].pNum++;

            linesNum++;
        }
        else
        {
            break;
        }
    }

    for (uint32_t i = 0; i < linesNum; i++)
    {
        for (uint32_t j = 1; j < lines[i].pNum; j++)
        {
            drawLine(lines[i].p[j - 1], lines[i].p[j]);
        }
    }

    //part 1
    /*
    uint32_t fallen = 0;

    while (dropSand(sandDrop))
    {
        fallen++;
    }

    printf("%d", fallen);
    */
    //part 2

    uint32_t fallen = 0;

    while (dropSand2(sandDrop))
    {
        fallen++;
    }

    printf("%d", fallen);

}

bool dropSand2(point_t p)
{
    int x = p.x;

    if (getGrid2(p.x, p.y) != AIR)
    {
        return false;
    }

    for (int y = p.y; y <= yMax + 1; y++)
    {
        if (getGrid2(x, y + 1) != AIR)
        {
            if (getGrid2(x - 1, y + 1) == AIR)
            {
                x--;
                continue;
            }
            else if (getGrid2(x + 1, y + 1) == AIR)
            {
                x++;
                continue;
            }
            else
            {
                grid[x][y] = SAND;
                return true;
            }
        }
    }

    return false;
}

ele_t getGrid2(int x, int y)
{
    if (y >= yMax + 2)
    {
        return ROCK;
    }

    return grid[x][y];
}


bool dropSand(point_t p)
{
    int x = p.x;
    for (int y = p.y; y <= yMax + 1; y++)
    {
        if (grid[x][y + 1] != AIR)
        {
            if (grid[x - 1][y + 1] == AIR)
            {
                x--;
                continue;
            }
            else if (grid[x + 1][y + 1] == AIR)
            {
                x++;
                continue;
            }
            else
            {
                grid[x][y] = SAND;
                return true;
            }
        }
    }

    return false;
}



void parsePt(point_t* p, string s)
{
    sscanf(s.c_str(), "%d,%d", &p->x, &p->y);

    xMax = max(xMax, p->x);
    yMax = max(yMax, p->y);

    xMin = min(xMin, p->x);
    yMin = min(yMin, p->y);
}

void drawLine(point_t p1, point_t p2)
{
    if (p1.x == p2.x && p1.y == p2.y)
    {
        printf("Unknown case 1");
        return;
    }
    if (p1.x == p2.x)
    {
        for (int y = min(p1.y, p2.y); y <= max(p1.y, p2.y); y++)
        {
            grid[p1.x][y] = ROCK;
        }
    }
    else if (p1.y == p2.y)
    {
        for (int x = min(p1.x, p2.x); x <= max(p1.x, p2.x); x++)
        {
            grid[x][p1.y] = ROCK;
        }
    }
    else
    {
        printf("Unknown case 2");
        return;
    }
}

void printGrid(void)
{
    for (int y = min(yMin, sandDrop.y); y <= yMax; y++)
    {
        for (int x = xMin; x <= xMax; x++)
        {
            char eleChr[ELE_MAX] = { '.', '#', 'o' };

            printf("%c", eleChr[grid[x][y]]);
        }
        printf("\r\n");
    }
    printf("\r\n");
}
