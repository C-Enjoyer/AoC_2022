// 11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <inttypes.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_MONKEE  8

typedef enum op
{
    ADD,
    MULT,
    SQUARE
} op_t;

typedef struct monkee
{
    uint64_t* items;
    uint32_t itemsNum;

    op_t op;
    uint32_t opVal;

    uint32_t divBy;

    uint32_t trueMon;
    uint32_t falseMon;

} monkee_t;

void removeItems(monkee_t* monkee);
void removeItem(monkee_t* monkee, uint64_t item);
void addItem(monkee_t* monkee, uint64_t item);

monkee_t monkee[MAX_MONKEE] = { 0 };
uint32_t monkeeNum = 0;

int main()
{
    bool prevEmtpy = false;
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
            if (line[0] == 'S')
            {
                uint32_t sep = line.find(':');
                for (uint32_t i = sep; i < line.length(); i++)
                {
                    if (line[i] == ',')
                    {
                        string numStr = line.substr(sep + 1, i - sep - 1);
                        uint32_t num = atoi(numStr.c_str());
                        addItem(&monkee[monkeeNum], num);
                        sep = i;
                    }
                }

                string numStr = line.substr(sep + 1, line.length() - sep);
                uint32_t num = atoi(numStr.c_str());
                addItem(&monkee[monkeeNum], num);
            }
            else if (line[0] == 'O')
            {
                uint32_t oper = line.find('+');
                if (oper != -1)
                {
                    monkee[monkeeNum].op = ADD;
                }
                else
                {
                    oper = line.find('*');
                    if (line[oper + 1] == 'o')
                    {
                        monkee[monkeeNum].op = SQUARE;
                    }
                    else
                    {
                        monkee[monkeeNum].op = MULT;
                    }
                }

                string numStr = line.substr(oper + 1, line.length() - oper);
                monkee[monkeeNum].opVal = atoi(numStr.c_str());
            }
            else if (line[0] == 'T')
            {
                uint32_t last = line.find('y');
                string numStr = line.substr(last + 1, line.length() - last);
                monkee[monkeeNum].divBy = atoi(numStr.c_str());
            }
            else if (line[0] == 'I')
            {
                uint32_t last = line.find('y');
                string numStr = line.substr(last + 1, line.length() - last);
                uint32_t num = atoi(numStr.c_str());

                if (line[2] == 't')
                {
                    monkee[monkeeNum].trueMon = num;
                }
                else
                {
                    monkee[monkeeNum].falseMon = num;
                }
            }

            prevEmtpy = false;
        }
        else
        {
            if (!prevEmtpy)
            {
                prevEmtpy = true;
                monkeeNum++;
            }
            else
            {
                break;
            }
        }
    }

    //part 1
    /*
    int inspects[MAX_MONKEE] = { 0 };

    for (uint32_t round = 0; round < 20; round++)
    {
        for (uint32_t i = 0; i < monkeeNum; i++)
        {
            for (uint32_t j = 0; j < monkee[i].itemsNum; j++)
            {
                uint64_t worry = monkee[i].items[j];
                

                if (monkee[i].op == ADD)
                {
                    worry += monkee[i].opVal;
                }
                else if (monkee[i].op == MULT)
                {
                    worry *= monkee[i].opVal;
                }
                else
                {
                    worry *= worry;
                }

                worry /= 3;

                if (worry % monkee[i].divBy == 0)
                {
                    addItem(&monkee[monkee[i].trueMon], worry);
                }
                else
                {
                    addItem(&monkee[monkee[i].falseMon], worry);
                }

                inspects[i]++;
            }
            removeItems(&monkee[i]);
        }
    }

    sort(inspects, &inspects[MAX_MONKEE]);

    int result = inspects[MAX_MONKEE - 1] * inspects[MAX_MONKEE - 2];
    printf("%d", result);
    */
    //part 2

    uint64_t mult = 1;

    for (uint32_t i = 0; i < monkeeNum; i++)
    {
        mult *= monkee[i].divBy;
    }

    uint64_t inspects[MAX_MONKEE] = { 0 };

    for (uint32_t round = 0; round < 10000; round++)
    {
        for (uint32_t i = 0; i < monkeeNum; i++)
        {
            for (uint32_t j = 0; j < monkee[i].itemsNum; j++)
            {
                uint64_t worry = monkee[i].items[j];


                if (monkee[i].op == ADD)
                {
                    worry += monkee[i].opVal;
                }
                else if (monkee[i].op == MULT)
                {
                    worry *= monkee[i].opVal;
                }
                else
                {
                    worry *= worry;
                }

                worry %= mult;

                if (worry % monkee[i].divBy == 0)
                {
                    addItem(&monkee[monkee[i].trueMon], worry);
                }
                else
                {
                    addItem(&monkee[monkee[i].falseMon], worry);
                }

                inspects[i]++;
            }
            removeItems(&monkee[i]);
        }
    }

    sort(inspects, &inspects[MAX_MONKEE]);

    uint64_t result = inspects[MAX_MONKEE - 1] * inspects[MAX_MONKEE - 2];
    printf("%" PRIu64, result);

}

void removeItems(monkee_t* monkee)
{
    monkee->itemsNum = 0;
}

void removeItem(monkee_t* monkee, uint64_t item)
{
    uint32_t itemNum = -1;
    for (uint32_t i = 0; i < monkee->itemsNum; i++)
    {
        if (monkee->items[i] == item)
        {
            itemNum = i;
            break;
        }
    }

    if (itemNum == -1)
    {
        printf("Monkee has no such item");
        return;
    }

    for (uint32_t i = itemNum + 1; i < monkee->itemsNum; i++)
    {
        monkee->items[i - 1] = monkee->items[i];
    }

    monkee->itemsNum--;
}

void addItem(monkee_t* monkee, uint64_t item)
{
    void* p = realloc(monkee->items, sizeof(*monkee->items) * (monkee->itemsNum + 1));
    if (p == NULL)
    {
        printf("No space left");
        return;
    }

    monkee->items = (uint64_t*) p;
    monkee->items[monkee->itemsNum] = item;
    monkee->itemsNum++;
}

