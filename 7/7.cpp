// 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_INSTR       5000
#define MAX_FILENAME    50
#define MAX_DIRNAME     50

typedef struct file
{
    char name[MAX_FILENAME];
    uint64_t size;

} file_t;

struct dir_t
{
    dir_t* upper;

    dir_t** lowers;
    uint32_t lowersNum;

    file_t** files;
    uint32_t filesNum;
    
    uint64_t size;
    char name[MAX_DIRNAME];
};

typedef enum instrType
{
    UNKNOWN,
    CD,
    LS,
    DIR,
    FILESZ

} instrType_t;

uint64_t addPart1(dir_t* dir, uint64_t curSum);
dir_t* findSmallestPossible(dir_t* dir, dir_t* best, uint64_t minFreeUp);
instrType_t getInstrType(string instr);
void addDir(dir_t* parent, string name);
void addFile(dir_t* dir, string name, uint64_t size);
void addSizeToDirRec(dir_t* dir, uint64_t size);
dir_t* cd(dir_t* curDir, string name);

string instr[MAX_INSTR] = {""};
uint32_t instrNum = 0;

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            instr[instrNum] = line;
            instrNum++;
        }
        else
        {
            break;
        }
    }

    dir_t tree = { NULL, NULL, 0, NULL, 0, 0, "root" };
    dir_t* curDir = &tree;

    for (uint32_t i = 0; i < instrNum; i++)
    {
        switch (getInstrType(instr[i]))
        {
            case CD:
            {
                string name = instr[i].substr(5, instr[i].size() - 5);

                if (name == "/")
                {
                    curDir = &tree;
                }
                else if (name == "..")
                {
                    if (curDir->upper != NULL)
                    {
                        curDir = curDir->upper;
                    }
                    else
                    {
                        printf("There is no upper directory\r\n");
                    }
                }
                else
                {
                    curDir = cd(curDir, name);
                }
            }
            break;
            case LS:
            {
                   // we can ignore that
            }
            break;
            case DIR:
            {
                string name = instr[i].substr(4, instr[i].size() - 4);

                addDir(curDir, name);
            }
            break;
            case FILESZ:
            {
                int size = 0;
                char nameCStr[MAX_FILENAME] = "";
                sscanf(instr[i].c_str(), "%d %s", &size, nameCStr);
                string name = nameCStr;

                addFile(curDir, name, size);
            }
            break;
            default:
                printf("Couldn't parse line %d\r\n", i);
            break;
        }
    }

    //part 1
    /*
    uint64_t result = addPart1(&tree, 0);
    printf("%d", result);
    */
    //part 2

    dir_t* best = findSmallestPossible(&tree, &tree, 30000000 - (70000000 - tree.size));
    printf("%d", best->size);
}

uint64_t addPart1(dir_t* dir, uint64_t curSum)
{
    if (dir->size <= 100000)
    {
        curSum += dir->size;
    }

    for (uint32_t i = 0; i < dir->lowersNum; i++)
    {
        curSum = addPart1(dir->lowers[i], curSum);
    }

    return curSum;
}

dir_t* findSmallestPossible(dir_t* dir, dir_t* best, uint64_t minFreeUp)
{
    if (minFreeUp <= dir->size && dir->size < best->size)
    {
        best = dir;
    }

    for (uint32_t i = 0; i < dir->lowersNum; i++)
    {
        best = findSmallestPossible(dir->lowers[i], best, minFreeUp);
    }

    return best;
}

instrType_t getInstrType(string instr)
{
    if (instr[0] == '$')
    {
        if (instr[2] == 'l')
        {
            return LS;
        }
        else if (instr[2] == 'c')
        {
            return CD;
        }
    }
    else if (instr[0] == 'd')
    {
        return DIR;
    }
    else if ('0' <= instr[0] && instr[0] <= '9')
    {
        return FILESZ;
    }

    return UNKNOWN;
}

void addDir(dir_t* parent, string name)
{
    for (uint32_t i = 0; i < parent->lowersNum; i++)
    {
        if (strcmp(parent->lowers[i]->name, name.c_str()) == 0)
        {
            printf("Dir already registered");
            return;
        }
    }

    dir_t* dir = (dir_t*) malloc(sizeof(dir_t));

    if (dir == NULL)
    {
        printf("No space for dir %s", name.c_str());
        return;
    }

    dir->upper = parent;
    strncpy(dir->name, name.c_str(), MAX_DIRNAME);
    dir->size = 0;
    dir->files = NULL;
    dir->filesNum = 0;
    dir->lowers = NULL;
    dir->lowersNum = 0;
    
    void *p = realloc(parent->lowers, sizeof(*parent->lowers) * (parent->lowersNum + 1));
    if (p == NULL)
    {
        printf("No space for dir in parent");
        return;
    }

    parent->lowers = (dir_t**) p;
    parent->lowers[parent->lowersNum] = dir;
    parent->lowersNum++;
}

void addFile(dir_t* dir, string name, uint64_t size)
{
    for (uint32_t i = 0; i < dir->filesNum; i++)
    {
        if (strcmp(dir->files[i]->name, name.c_str()) == 0)
        {
            printf("File already registered");
            return;
        }
    }

    file_t* file = (file_t*) malloc(sizeof(file_t));

    if (file == NULL)
    {
        printf("No space for file %s", name.c_str());
        return;
    }

    strncpy(file->name, name.c_str(), MAX_FILENAME);
    file->size = size;

    void* p = realloc(dir->files, sizeof(*dir->files) * (dir->filesNum + 1));
    if (p == NULL)
    {
        printf("No space for file in dir");
        return;
    }

    dir->files = (file_t**) p;
    dir->files[dir->filesNum] = file;
    dir->filesNum++;

    addSizeToDirRec(dir, size);
}

void addSizeToDirRec(dir_t* dir, uint64_t size)
{
    if (dir == NULL)
    {
        return;
    }

    dir->size += size;

    if (dir->upper != NULL)
    {
        addSizeToDirRec(dir->upper, size);
    }
}

dir_t* cd(dir_t* curDir, string name)
{
    for (uint32_t i = 0; i < curDir->lowersNum; i++)
    {
        if (strcmp(curDir->lowers[i]->name, name.c_str()) == 0)
        {
            return curDir->lowers[i];
        }
    }

    printf("dir %s not found\r\n", name.c_str());
    return curDir;
}
