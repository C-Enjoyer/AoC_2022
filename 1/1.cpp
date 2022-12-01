// 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_ELF 2000

uint32_t elfCal[MAX_ELF] = { 0 };
uint32_t elfCalNum = 0;

int main()
{
    bool prevEmpty = false;
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            prevEmpty = false;
            uint32_t num = 0;

            sscanf(line.c_str(), "%d", &num);
            elfCal[elfCalNum] += num;
        }
        else
        {
            elfCalNum++;
            if (prevEmpty)
            {
                break;
            }
            else
            {
                prevEmpty = true;
            }
        }
    }

    //part 1
    /*uint32_t res = *max_element(elfCal, elfCal + elfCalNum);
    printf("%d", res);*/

    //part 2
    sort(elfCal, elfCal + elfCalNum);
    uint32_t res = elfCal[elfCalNum - 1] + elfCal[elfCalNum - 2] + elfCal[elfCalNum - 3];

    printf("%d", res);
}
