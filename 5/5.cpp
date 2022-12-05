// 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

typedef struct move
{
    uint32_t num;
    uint32_t src;
    uint32_t dst;
} move_t;

#define MAX_MOVES   5000
#define MAX_HEIGHT  100


// I chose a coding challenge instead of a parsing massacre
#define CRATES_NUM  9
string crates[CRATES_NUM] =
{
    "JHPMSFNV",
    "SRLMJDQ",
    "NQDHCSWB",
    "RSCL",
    "MVTPFB",
    "TRQNC",
    "GVR",
    "CZSPDLR",
    "DSJVGPBF"
};

void moveTo(string* dst, string* src, uint32_t num);
void moveToStacked(string* dst, string* src, uint32_t num);

move_t moves[MAX_MOVES] = { 0 };
uint32_t movesNum = 0;

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            sscanf(line.c_str(), "move %d from %d to %d", &moves[movesNum].num, &moves[movesNum].src, &moves[movesNum].dst);
            movesNum++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    string res = "";

    for (uint32_t i = 0; i < movesNum; i++)
    {
        moveTo(&crates[moves[i].dst - 1], &crates[moves[i].src - 1], moves[i].num);
    }

    for (uint32_t i = 0; i < CRATES_NUM; i++)
    {
        res += crates[i].back();
    }

    printf("%s", res.c_str());
    */
    //part 2

    string res = "";

    for (uint32_t i = 0; i < movesNum; i++)
    {
        moveToStacked(&crates[moves[i].dst - 1], &crates[moves[i].src - 1], moves[i].num);
    }

    for (uint32_t i = 0; i < CRATES_NUM; i++)
    {
        res += crates[i].back();
    }

    printf("%s", res.c_str());

}

void moveTo(string* dst, string* src, uint32_t num)
{
    string rev = src->substr(src->length() - num, num);
    reverse(rev.begin(), rev.end());
    *dst += rev;

    src->erase(src->end() - num, src->end());
}

void moveToStacked(string* dst, string* src, uint32_t num)
{
    string stack = src->substr(src->length() - num, num);
    *dst += stack;

    src->erase(src->end() - num, src->end());
}
