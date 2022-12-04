// 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_LINE    5000

typedef struct range
{
    uint32_t min, max;
} range_t;

typedef struct combo
{
    range_t left;
    range_t right;
} combo_t;

bool contains(range_t range1, range_t range2);
bool isWithin(range_t range1, range_t range2);

combo_t combo[MAX_LINE] = { 0 };
uint32_t comboNum = 0;

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            sscanf(line.c_str(), "%d-%d,%d-%d", &combo[comboNum].left.min, &combo[comboNum].left.max, &combo[comboNum].right.min, &combo[comboNum].right.max);
            comboNum++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    uint32_t res = 0;

    for (uint32_t i = 0; i < comboNum; i++)
    {
        if (contains(combo[i].left, combo[i].right) || contains(combo[i].right, combo[i].left))
        {
            res++;
        }
    }

    printf("%d", res);
    */
    //part 2

    uint32_t res = 0;

    for (uint32_t i = 0; i < comboNum; i++)
    {
        if (isWithin(combo[i].left, combo[i].right) || isWithin(combo[i].right, combo[i].left))
        {
            res++;
        }
    }

    printf("%d", res);
}

bool contains(range_t range1, range_t range2)
{
    return (range1.min <= range2.min && range1.max >= range2.max);
}

bool isWithin(range_t range1, range_t range2)
{
    return (range1.min <= range2.min && range2.min <= range1.max
         || range1.min <= range2.max && range2.max <= range1.max);
}
