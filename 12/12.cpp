// 12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_X   200
#define MAX_Y   200

typedef struct coord
{
    int x;
    int y;
} coord_t;

bool check(coord_t c);
bool isValidCoord(coord_t c);

char grid[MAX_X][MAX_Y] = { '\0' };
uint32_t gridX = 0;
uint32_t gridY = 0;

coord_t startC = { 0 };
coord_t endC = { 0 };

int num[MAX_X][MAX_Y] = { 0 };

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            for (uint32_t i = 0; i < line.length(); i++)
            {
                if (line[i] == 'S')
                {
                    startC.x = i;
                    startC.y = gridY;
                    line[i] = 'a';
                }
                else if (line[i] == 'E')
                {
                    endC.x = i;
                    endC.y = gridY;
                    line[i] = 'z';
                }
                grid[i][gridY] = line[i];
            }
            gridX = line.length();
            gridY++;
        }
        else
        {
            break;
        }
    }

    for (uint32_t x = 0; x < gridX; x++)
    {
        for (uint32_t y = 0; y < gridX; y++)
        {
            num[x][y] = INT_MAX;
        }
    }

    num[endC.x][endC.y] = 0;

    uint32_t changes = 0;
    do
    {
        changes = 0;

        for (int x = 0; x < gridX; x++)
        {
            for (int y = 0; y < gridY; y++)
            {
                changes += check({ x, y });
            }
        }

    } while (changes != 0);

    //part 1
    /*
    printf("%d", num[startC.x][startC.y]);
    */
    //part 2

    int result = INT_MAX;

    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            if (grid[x][y] == 'a')
            {
                result = min(result, num[x][y]);
            }
        }
    }

    printf("%d", result);

}

bool check(coord_t c)
{
    coord_t sides[] = {
        { c.x - 1, c.y },
        { c.x + 1, c.y },
        { c.x, c.y - 1},
        { c.x, c.y + 1 }
    };
    uint32_t sidesNum = sizeof(sides) / sizeof(sides[0]);

    int prevNum = num[c.x][c.y];

    for (uint32_t i = 0; i < sidesNum; i++)
    {
        if (!isValidCoord(sides[i]))
        {
            continue;
        }

        if (num[c.x][c.y] > num[sides[i].x][sides[i].y])
        {
            if (grid[c.x][c.y] >= grid[sides[i].x][sides[i].y] - 1)
            {
                num[c.x][c.y] = min(num[c.x][c.y], num[sides[i].x][sides[i].y] + 1);
            }
        }
    }

    return prevNum != num[c.x][c.y];
}

bool isValidCoord(coord_t c)
{
    return c.x >= 0 && c.x < gridX&& c.y >= 0 && c.y < gridY;
}