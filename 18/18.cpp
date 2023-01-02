#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_PT      5000
#define MAX_GRID_X  30
#define MAX_GRID_Y  30
#define MAX_GRID_Z  30

#define TTL     15  //could take very long

typedef struct pt
{
    int x, y, z;
} pt_t;

typedef enum mat
{
    AIR,
    PT,
    VOID,
    TOUCHVOID,

} mat_t;

uint32_t getFreeSur(uint32_t ptNum);
void fill(void);
bool isPt(pt_t pt);
uint32_t getLavaSur(uint32_t ptNum);
bool reachesVoid(pt_t pt, uint32_t ttl);
mat_t getGrid(pt_t pt);

pt_t pts[MAX_PT] = { 0 };
uint32_t ptsNum = 0;

mat_t grid[MAX_GRID_X + 1][MAX_GRID_Y + 1][MAX_GRID_Z + 1] = { VOID };

pt_t ptDif[6] = { { -1,0,0 }, { 1,0,0 }, { 0,-1,0 }, { 0,1,0 }, { 0,0,-1 }, { 0,0,1 } };

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            sscanf(line.c_str(), "%d,%d,%d", &pts[ptsNum].x, &pts[ptsNum].y, &pts[ptsNum].z);
            ptsNum++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    uint32_t result = 0;

    for (uint32_t i = 0; i < ptsNum; i++)
    {
        result += getFreeSur(i);
    }

    printf("%d", result);
    */
    //part 2

    fill();

    uint32_t result = 0;

    for (uint32_t i = 0; i < ptsNum; i++)
    {
        result += getLavaSur(i);
        printf("%d/%d\r\n", i + 1, ptsNum);
    }

    printf("%d", result);

}

void fill(void)
{
    for (uint32_t i = 0; i < ptsNum; i++)
    {
        grid[pts[i].x][pts[i].y][pts[i].z] = PT;
    }
}

mat_t getGrid(pt_t pt)
{
    if (pt.x < 0 || pt.y < 0 || pt.z < 0)
    {
        return VOID;
    }

    if (pt.x > MAX_GRID_X || pt.y > MAX_GRID_Y || pt.z > MAX_GRID_Z)
    {
        return VOID;
    }

    return grid[pt.x][pt.y][pt.z];
}

bool isPt(pt_t pt)
{
    for (uint32_t i = 0; i < ptsNum; i++)
    {
        if (pt.x == pts[i].x && pt.y == pts[i].y && pt.z == pts[i].z)
        {
            return true;
        }
    }

    return false;
}

uint32_t getLavaSur(uint32_t ptNum)
{
    uint32_t num = 6;
    pt_t pt = pts[ptNum];

    for (pt_t ptd : ptDif)
    {
        pt_t ptg = { pt.x + ptd.x, pt.y + ptd.y, pt.z + ptd.z };

        if (getGrid(ptg) == PT || !reachesVoid(ptg, TTL))
        {
            num--;
        }
    }

    return num;
}

bool reachesVoid(pt_t pt, uint32_t ttl)
{
    if (getGrid(pt) == VOID)
    {
        return true;
    }

    if (getGrid(pt) == TOUCHVOID)
    {
        return true;
    }

    if (getGrid(pt) == PT)
    {
        return false;
    }

    if (ttl == 0)
    {
        return false;
    }

    ttl--;

    for (const pt_t &ptd : ptDif)
    {
        pt_t ptg = { pt.x + ptd.x, pt.y + ptd.y, pt.z + ptd.z };

        if (reachesVoid(ptg, ttl))
        {
            grid[pt.x][pt.y][pt.z] = TOUCHVOID;
            return true;
        }
    }

    return false;
}

uint32_t getFreeSur(uint32_t ptNum)
{
    uint32_t num = 6;
    pt_t pt = pts[ptNum];

    for (uint32_t i = 0; i < ptsNum; i++)
    {
        if (i == ptNum)
        {
            continue;
        }

        for (int x = pt.x - 1; x <= pt.x + 1; x++)
        {
            for (int y = pt.y - 1; y <= pt.y + 1; y++)
            {
                for (int z = pt.z - 1; z <= pt.z + 1; z++)
                {
                    uint32_t dis = abs(pt.x - x) + abs(pt.y - y) + abs(pt.z - z);
                    if (dis > 1 || (x == pt.x && y == pt.y && z == pt.z))
                    {
                        continue;
                    }

                    if (pts[i].x == x && pts[i].y == y && pts[i].z == z)
                    {
                        num--;
                    }
                }
            }
        }
    }

    return num;
}
