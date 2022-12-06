// 6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

string code = "";

bool hasDuplicateChar(string str);

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            code = line;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    uint32_t res = 0;

    for (uint32_t i = 0; i < code.length(); i++)
    {
        if (!hasDuplicateChar(code.substr(i, 4)))
        {
            res = i + 4;
            break;
        }
    }

    printf("%d", res);
    */
    //part 2

    uint32_t res = 0;

    for (uint32_t i = 0; i < code.length(); i++)
    {
        if (!hasDuplicateChar(code.substr(i, 14)))
        {
            res = i + 14;
            break;
        }
    }

    printf("%d", res);

}

bool hasDuplicateChar(string str)
{
    for (uint32_t i = 0; i < str.length(); i++)
    {
        for (uint32_t j = 0; j < str.length(); j++)
        {
            if (i == j)
            {
                break;
            }

            if (str[i] == str[j])
            {
                return true;
            }
        }
    }

    return false;
}