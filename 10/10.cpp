// 10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_INSTR   5000

typedef enum instrType
{
    ADD,
    NOOP,

}instrType_t;

typedef struct instr
{
    instrType_t type;
    int num;

} instr_t;

int cycle(uint32_t cycle, int sum);
void cycle2(uint32_t cycle, int sum);

instr_t instr[MAX_INSTR];
uint32_t instrNum = 0;

uint32_t cycleRel[] = { 20, 60, 100, 140, 180, 220 };
uint32_t cycleRelNum = sizeof(cycleRel) / sizeof(cycleRel[0]);

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            if (line[0] == 'a')
            {
                char useless[5] = "";
                sscanf(line.c_str(), "%s %d", useless, &instr[instrNum].num);
                instr[instrNum].type = ADD;
            }
            else
            {
                instr[instrNum].type = NOOP;
                instr[instrNum].num = 0;
            }

            instrNum++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    uint32_t cycles = 0;
    int sum = 1;
    int result = 0;

    for (uint32_t i = 0; i < instrNum; i++)
    {
        if (instr[i].type == ADD)
        {
            cycles++;
            result += cycle(cycles, sum);
            cycles++;
            result += cycle(cycles, sum);
            sum += instr[i].num;
        }
        else
        {
            cycles ++;
            result += cycle(cycles, sum);
        }
    }
    
    printf("%d", result);
    */
    //part 2

    uint32_t cycles = 0;
    int sum = 1;

    for (uint32_t i = 0; i < instrNum; i++)
    {
        if (instr[i].type == ADD)
        {
            cycles++;
            cycle2(cycles, sum);
            cycles++;
            cycle2(cycles, sum);
            sum += instr[i].num;
        }
        else
        {
            cycles++;
            cycle2(cycles, sum);
        }
    }

}

int cycle(uint32_t cycle, int sum)
{
    for (uint32_t i = 0; i < cycleRelNum; i++)
    {
        if (cycle == cycleRel[i])
        {
            return cycleRel[i] * sum;
        }
    }

    return 0;
}

void cycle2(uint32_t cycle, int sum)
{
    char c = ' '; //empty block
    int pos = ((cycle - 1) % 40);
    if (sum - 1 <= pos && pos <= sum + 1)
    {
        c = 219; //full block
    }

    printf("%c", c);

    if (pos == 40 - 1)
    {
        printf("\r\n");
    }
}
