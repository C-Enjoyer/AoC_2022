// 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_ROUND   10000

uint32_t getPoints(void);

typedef struct round
{
    char op;
    char me;

} round_t;

round_t rounds[MAX_ROUND] = { 0 };
uint32_t roundsNum = 0;

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            char op, me;
            sscanf(line.c_str(), "%c %c", &rounds[roundsNum].op, &rounds[roundsNum].me);

            roundsNum++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    for (uint32_t i = 0; i < roundsNum; i++)
    {
        if (rounds[i].me == 'X') rounds[i].me = 'A';
        else if (rounds[i].me == 'Y') rounds[i].me = 'B';
        else if (rounds[i].me == 'Z') rounds[i].me = 'C';
    }

    printf("%d", getPoints());
    */
    //part 2
    
    for (uint32_t i = 0; i < roundsNum; i++)
    {
        if (rounds[i].me == 'X')
        {
            if (rounds[i].op == 'A') rounds[i].me = 'C';
            else if (rounds[i].op == 'B') rounds[i].me = 'A';
            else if (rounds[i].op == 'C') rounds[i].me = 'B';
        }
        else if (rounds[i].me == 'Y')
        {
            rounds[i].me = rounds[i].op;
        }
        else if (rounds[i].me == 'Z')
        {
            if (rounds[i].op == 'A') rounds[i].me = 'B';
            else if (rounds[i].op == 'B') rounds[i].me = 'C';
            else if (rounds[i].op == 'C') rounds[i].me = 'A';
        }
    }

    printf("%d", getPoints());

}

uint32_t getPoints(void)
{
    uint32_t points = 0;

    for (uint32_t i = 0; i < roundsNum; i++)
    {
        if (rounds[i].me == rounds[i].op)
        {
            points += 3;
        }
        else if (rounds[i].me == 'A' && rounds[i].op == 'C'
            || rounds[i].me == 'B' && rounds[i].op == 'A'
            || rounds[i].me == 'C' && rounds[i].op == 'B')
        {
            points += 6;
        }

        points += (rounds[i].me - 'A' + 1);
    }

    return points;
}
