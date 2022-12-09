// 9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_MOVES   10000
#define MAX_COORD   10000
#define KNOTS       10

typedef struct move
{
    char dir;
    uint8_t num;

} move_t;

typedef struct coord
{
    int x, y;
} coord_t;

bool isOutOfReach(coord_t head, coord_t tail);
coord_t getDistance(coord_t head, coord_t tail);
void addTailCoord(coord_t coord);

move_t moves[MAX_MOVES] = { 0 };
uint32_t movesNum = 0;

coord_t tailArr[MAX_COORD] = { 0 };
uint32_t tailArrNum = 0;

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            sscanf(line.c_str(), "%c %d", &moves[movesNum].dir, &moves[movesNum].num);
            movesNum++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    coord_t head = { 0, 0 };
    coord_t tail = { 0, 0 };

    addTailCoord(tail);

    for (uint32_t i = 0; i < movesNum; i++)
    {
        coord_t go = { 0, 0 };

        switch (moves[i].dir)
        {
            case 'U':
                go.y = 1;
            break;
            case 'D':
                go.y = -1;
            break;
            case 'L':
                go.x = -1;
            break;
            case 'R':
                go.x = 1;
            break;
        }

        for (uint32_t j = 0; j < moves[i].num; j++)
        {
            head.x += go.x;
            head.y += go.y;

            if (isOutOfReach(head, tail))
            {
                coord_t dis = getDistance(head, tail);

                if (abs(dis.x) > 1)
                {
                    tail.x += go.x;
                }
                else if (abs(dis.y) > 1)
                {
                    tail.y += go.y;
                }

                if (abs(dis.x) > 1 && dis.y != 0)
                {
                    tail.y += dis.y;
                }
                else if (abs(dis.y) > 1 && dis.x != 0)
                {
                    tail.x += dis.x;
                }

                addTailCoord(tail);
            }
        }


    }

    printf("%d", tailArrNum);
    */
    //part 2

    coord_t knots[KNOTS] = { 0 };

    addTailCoord(knots[KNOTS - 1]);

    for (uint32_t i = 0; i < movesNum; i++)
    {
        coord_t go = { 0, 0 };

        switch (moves[i].dir)
        {
        case 'U':
            go.y = 1;
            break;
        case 'D':
            go.y = -1;
            break;
        case 'L':
            go.x = -1;
            break;
        case 'R':
            go.x = 1;
            break;
        }

        for (uint32_t j = 0; j < moves[i].num; j++)
        {
            knots[0].x += go.x;
            knots[0].y += go.y;

            for (uint32_t k = 1; k < KNOTS; k++)
            {
                coord_t* head = &knots[k - 1];
                coord_t* tail = &knots[k];

                if (isOutOfReach(*head, *tail))
                {
                    coord_t dis = getDistance(*head, *tail);

                    if (abs(dis.x) > 1)
                    {
                        tail->x += dis.x > 0 ? 1 : -1;
                    }
                    else if (abs(dis.y) > 1)
                    {
                        tail->y += dis.y > 0 ? 1 : -1;
                    }

                    if (abs(dis.x) > 1 && dis.y != 0)
                    {
                        if (abs(dis.y) > 1)
                        {
                            tail->y += dis.y > 0 ? 1 : -1;
                        }
                        else
                        {
                            tail->y += dis.y;
                        }
                    }
                    else if (abs(dis.y) > 1 && dis.x != 0)
                    {
                        if (abs(dis.x) > 1)
                        {
                            tail->x += dis.x > 0 ? 1 : -1;
                        }
                        else
                        {
                            tail->x += dis.x;
                        }
                        
                    }

                    if (k == KNOTS - 1)
                    {
                        addTailCoord(*tail);
                    }
                }
            }
        }
    }

    printf("%d", tailArrNum);
}

bool isOutOfReach(coord_t head, coord_t tail)
{
    coord_t dis = getDistance(head, tail);
    return abs(dis.x) > 1 || abs(dis.y) > 1;
}

coord_t getDistance(coord_t head, coord_t tail)
{
    coord_t dis = { head.x - tail.x, head.y - tail.y };
    return dis;
}

void addTailCoord(coord_t coord)
{
    for (uint32_t i = 0; i < tailArrNum; i++)
    {
        if (tailArr[i].x == coord.x && tailArr[i].y == coord.y)
        {
            return;
        }
    }

    tailArr[tailArrNum].x = coord.x;
    tailArr[tailArrNum].y = coord.y;
    tailArrNum++;
}
