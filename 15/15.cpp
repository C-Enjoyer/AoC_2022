// 15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>
#include <inttypes.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_SENS 100

typedef struct pt
{
    int64_t x, y;
} pt_t;

typedef struct sens
{
    pt_t pt;
    pt_t beac;
    int64_t manDis;
} sens_t;

int64_t getManDis(pt_t p1, pt_t p2);
bool isBeac(pt_t p1);

sens_t sens[MAX_SENS] = { 0 };
uint32_t sensNum = 0;

int64_t xMin = INT_MAX;
int64_t xMax = 0;
int64_t yMin = INT_MAX;
int64_t yMax = 0;

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            sscanf(line.c_str(), "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld", &sens[sensNum].pt.x, &sens[sensNum].pt.y, &sens[sensNum].beac.x, &sens[sensNum].beac.y);
            
            sens[sensNum].manDis = getManDis(sens[sensNum].pt, sens[sensNum].beac);

            xMin = min(xMin, sens[sensNum].pt.x - sens[sensNum].manDis);
            xMax = max(xMax, sens[sensNum].pt.x + sens[sensNum].manDis);
            yMin = min(yMin, sens[sensNum].pt.y - sens[sensNum].manDis);
            yMax = max(yMax, sens[sensNum].pt.y + sens[sensNum].manDis);

            sensNum++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    uint32_t result = 0;
    int64_t y = 2000000;

    for (int64_t x = xMin; x <= xMax; x++)
    {
        for (uint32_t i = 0; i < sensNum; i++)
        {
            if (getManDis(sens[i].pt, { x, y }) <= sens[i].manDis && !isBeac({x, y}))
            {
                result++;
                break;
            }
        }
    }

    printf("%d", result);
    */
    //part 2
    
    pt_t beac = { 0, 0 };
    int64_t maxCoord = 4000000;

    for (int64_t x = 0; x <= maxCoord; x++)
    {
        for (int64_t y = 0; y <= maxCoord; y++)
        {
            bool success = true;
            for (uint32_t i = 0; i < sensNum; i++)
            {
                int64_t man = getManDis(sens[i].pt, { x, y });
                if (man <= sens[i].manDis)
                {
                    y += sens[i].manDis - man;
                    success = false;
                    break;
                }
            }

            if (success)
            {
                beac.x = x;
                beac.y = y;
                goto finished;
            }
        }

        if (x % 100000 == 0)
        {
            printf("x = %" PRId64 "\r\n", x);
        }
    }

    finished:

    int64_t result = beac.x * 4000000 + beac.y;
    printf("%" PRId64, result);
}

int64_t getManDis(pt_t p1, pt_t p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

bool isBeac(pt_t p1)
{
    for (uint32_t i = 0; i < sensNum; i++)
    {
        if (sens[i].beac.x == p1.x && sens[i].beac.y == p1.y)
        {
            return true;
        }
    }

    return false;
}
