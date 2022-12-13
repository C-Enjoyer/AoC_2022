// 13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_PAIR    1000
#define MAX_LINE    2000

struct ele_t
{
    uint32_t id;

    bool isNum;
    uint32_t num;

    ele_t** eles;
    uint32_t elesNum;
};

typedef struct pair
{
    ele_t *ele1;
    ele_t *ele2;

} pair_t;

int qsortEle(const void* a, const void* b);
int compareEle(ele_t* ele1, ele_t* ele2);
ele_t* intEleToListEle(ele_t* ele);
ele_t* parseEle(char** str);
void addEle(ele_t* p, ele_t* c);

pair_t pairs[MAX_PAIR] = { 0 };
uint32_t pairsNum = 0;
bool pairsFirst = true;

ele_t* list[MAX_PAIR / 2] = { 0 };
uint32_t listNum = 0;

int main()
{
    bool prevEmpty = false;
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            char str[MAX_LINE] = { 0 };
            char* strPt = str;
            strcpy(str, line.c_str());

            list[listNum] = parseEle(&strPt);

            if (pairsFirst)
            {
                pairs[pairsNum].ele1 = list[listNum];
            }
            else
            {
                pairs[pairsNum].ele2 = list[listNum];
            }


            listNum++;
            pairsFirst = !pairsFirst;
            prevEmpty = false;
        }
        else
        {
            if (!prevEmpty)
            {
                pairsNum++;
                prevEmpty = true;
            }
            else
            {
                break;
            }
        }
    }

    //part 1
    /*
    uint32_t result = 0;

    for (uint32_t i = 0; i < pairsNum; i++)
    {
        if (compareEle(pairs[i].ele1, pairs[i].ele2) >= 0)
        {
            result += (i + 1);
        }
    }

    printf("%d", result);
    */
    //part 2
    
    char p2[] = "[[2]]";
    char* pp2 = p2;

    char p6[] = "[[6]]";
    char* pp6 = p6;

    list[listNum] = parseEle(&pp2);
    list[listNum]->id = 1;
    listNum++;
    list[listNum] = parseEle(&pp6);
    list[listNum]->id = 1;
    listNum++;

    qsort(list, listNum, sizeof(ele_t*), qsortEle);


    uint32_t result = 1;

    for (uint32_t i = 0; i < listNum; i++)
    {
        if (list[i]->id == 1)
        {
            result *= (i + 1);
        }
    }

    printf("%d", result);

}

int qsortEle(const void* a, const void* b)
{
    return -compareEle(*(ele_t**)a, *(ele_t**)b);
}

int compareEle(ele_t* ele1, ele_t* ele2)
{
    if (ele1->isNum && ele2->isNum)
    {
        return ele2->num - ele1->num;
    }
    if (!ele1->isNum && !ele2->isNum)
    {
        uint32_t elesNum = min(ele1->elesNum, ele2->elesNum);
        for (uint32_t i = 0; i < elesNum; i++)
        {
            int res = compareEle(ele1->eles[i], ele2->eles[i]);
            if (res)
            {
                return res;
            }
        }

        return ele2->elesNum - ele1->elesNum;
    }

    if (ele1->isNum)
    {
        ele1 = intEleToListEle(ele1);
    }

    if (ele2->isNum)
    {
        ele2 = intEleToListEle(ele2);
    }

    return compareEle(ele1, ele2);
}

ele_t* intEleToListEle(ele_t* ele)
{
    ele_t* inside = (ele_t*) calloc(1, sizeof(ele_t));
    if (inside == NULL)
    {
        printf("No space left");
        return NULL;
    }

    ele_t* ret = (ele_t*) calloc(1, sizeof(ele_t));
    if (ret == NULL)
    {
        printf("No space left");
        return NULL;
    }

    inside->isNum = true;
    inside->num = ele->num;

    addEle(ret, inside);

    return ret;
}

ele_t* parseEle(char** str)
{
    ele_t* ele = (ele_t*) calloc(1, sizeof(ele_t));
    if (ele == NULL)
    {
        printf("No space left");
        return NULL;
    }

    if ('0' <= **str && **str <= '9')
    {
        ele->isNum = true;
        ele->num = strtol(*str, str, 0);

        return ele;
    }

    (*str)++;

    while(**str)
    {
        if (**str == ']')
        {
            break;
        }
        else if(**str == ',')
        {
            (*str)++;
            continue;
        }

        addEle(ele, parseEle(str));
    }

    (*str)++;

    return ele;
}

void addEle(ele_t* p, ele_t* c)
{
    void* pt = realloc(p->eles, sizeof(*p->eles) * (p->elesNum + 1));
    if (pt == NULL)
    {
        printf("No space left");
        return;
    }

    p->eles = (ele_t**) pt;
    p->eles[p->elesNum] = c;
    p->elesNum++;
}
