// 8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_X   500
#define MAX_Y   500

uint8_t grid[MAX_X][MAX_Y] = { 0 };
uint32_t gridX = 0;
uint32_t gridY = 0;

bool checkTop(int xcur, int ycur);
bool checkBot(int xcur, int ycur);
bool checkLeft(int xcur, int ycur);
bool checkRight(int xcur, int ycur);

int countTop(int xcur, int ycur);
int countBot(int xcur, int ycur);
int countLeft(int xcur, int ycur);
int countRight(int xcur, int ycur);

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
                grid[i][gridY] = line[i] - '0';
            }

            gridX = line.length();
            gridY++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    uint32_t result = gridX * 2 + gridY * 2 - 4;
    for (int x = 1; x < gridX - 1; x++)
    {
        for (int y = 1; y < gridY - 1; y++)
        {
            if (checkTop(x, y) || checkBot(x, y) || checkLeft(x, y) || checkRight(x, y))
            {
                result++;
            }
        }
    }

    printf("%d", result);
    */
    //part 2
    uint32_t best = 0;
    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            uint32_t top = countTop(x, y);
            uint32_t bot = countBot(x, y);
            uint32_t left = countLeft(x, y);
            uint32_t right = countRight(x, y);

            uint32_t cur = top * bot * left * right;

            if (cur > best)
            {
                best = cur;
            }
        }
    }

    printf("%d", best);

}

int countTop(int xcur, int ycur)
{
    int cnt = 0;
    for (int y = ycur - 1; y >= 0; y--)
    {
        cnt++;
        if (grid[xcur][y] >= grid[xcur][ycur])
        {
            break;
        }
    }
    return cnt;
}

int countBot(int xcur, int ycur)
{
    int cnt = 0;
    for (int y = ycur + 1; y < gridY; y++)
    {
        cnt++;
        if (grid[xcur][y] >= grid[xcur][ycur])
        {
            break;
        }
    }
    return cnt;
}

int countLeft(int xcur, int ycur)
{
    int cnt = 0;
    for (int x = xcur - 1; x >= 0; x--)
    {
        cnt++;
        if (grid[x][ycur] >= grid[xcur][ycur])
        {
            break;
        }
    }
    return cnt;
}

int countRight(int xcur, int ycur)
{
    int cnt = 0;
    for (int x = xcur + 1; x < gridX; x++)
    {
        cnt++;
        if (grid[x][ycur] >= grid[xcur][ycur])
        {
            break;
        }
    }
    return cnt;
}

bool checkTop(int xcur, int ycur)
{
    uint8_t curVal = grid[xcur][ycur];
    for (int y = ycur - 1; y >= 0; y--)
    {
        if (grid[xcur][y] >= curVal)
        {
            return false;
        }
    }
    return true;
}

bool checkBot(int xcur, int ycur)
{
    uint8_t curVal = grid[xcur][ycur];
    for (int y = ycur + 1; y < gridY; y++)
    {
        if (grid[xcur][y] >= curVal)
        {
            return false;
        }
    }
    return true;
}

bool checkLeft(int xcur, int ycur)
{
    uint8_t curVal = grid[xcur][ycur];
    for (int x = xcur - 1; x >= 0; x--)
    {
        if (grid[x][ycur] >= curVal)
        {
            return false;
        }
    }
    return true;
}

bool checkRight(int xcur, int ycur)
{
    uint8_t curVal = grid[xcur][ycur];
    for (int x = xcur + 1; x < gridX; x++)
    {
        if (grid[x][ycur] >= curVal)
        {
            return false;
        }
    }
    return true;
}

