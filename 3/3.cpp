// 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_IN 10000

char getCommonChar(string s1, string s2);
string getCommonString(string s1, string s2);
uint32_t getPoints(char c);

typedef struct ruck
{
    string comp1;
    string comp2;
} ruck_t;

ruck_t ruck[MAX_IN];
uint32_t ruckNum = 0;

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            ruck[ruckNum].comp1 = line.substr(0, line.length() / 2);
            ruck[ruckNum].comp2 = line.substr(line.length() / 2);

            ruckNum++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    uint32_t res = 0;

    for (uint32_t i = 0; i < ruckNum; i++)
    {
        char c = getCommonChar(ruck[i].comp1, ruck[i].comp2);
        res += getPoints(c);
    }

    printf("%d", res);
    */
    //part 2
    
    uint32_t res = 0;

    for (uint32_t i = 0; i < ruckNum; i+=3)
    {
        string r1 = ruck[i].comp1 + ruck[i].comp2;
        string r2 = ruck[i+1].comp1 + ruck[i+1].comp2;
        string r3 = ruck[i+2].comp1 + ruck[i+2].comp2;

        string r1r2 = getCommonString(r1, r2);
        char c = getCommonChar(r1r2, r3);
      
        res += getPoints(c);
    }

    printf("%d", res);
    
}

char getCommonChar(string s1, string s2)
{
    for (uint32_t i = 0; i < s1.length(); i++)
    {
        for (uint32_t j = 0; j < s2.length(); j++)
        {
            if (s1[i] == s2[j])
            {
                return s1[i];
            }
        }
    }

    return '\0';
}

string getCommonString(string s1, string s2)
{
    string str = "";

    for (uint32_t i = 0; i < s1.length(); i++)
    {
        for (uint32_t j = 0; j < s2.length(); j++)
        {
            if (s1[i] == s2[j])
            {
                str += s1[i];
            }
        }
    }

    return str;
}

uint32_t getPoints(char c)
{
    if ('a' <= c && c <= 'z')
    {
        return (c + 1 - 'a');
    }
    else if ('A' <= c && c <= 'Z')
    {
        return (c + 27 - 'A');
    }
}