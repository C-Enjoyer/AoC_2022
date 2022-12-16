#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include <tuple>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_VALVES  100
#define MAX_PATHS   6

#define ITER_T tuple<uint64_t, uint64_t, uint64_t, uint8_t>

struct valve_t
{
    char id[2 + 1];
    uint32_t flow;

    char ids[MAX_PATHS][2 + 1];
    uint32_t idsNum;
};

typedef struct iter
{
    uint64_t valve;
    uint64_t doneReg;
    uint64_t timeLeft;
    uint8_t person;

} iter_t;

uint64_t getValveNum(char* id);
uint64_t checkValve(iter_t iter);

valve_t valves[MAX_VALVES] = { 0 };
uint64_t valvesNum = 0;

uint64_t AA = 0;

vector<uint64_t> flows;
vector<vector<uint64_t>> connections;
map<ITER_T, uint64_t> results;

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            char pathsStr[50 + 1] = "";
            sscanf(line.c_str(), "Valve %2s has flow rate=%d; tunnels lead to valves", valves[valvesNum].id, &valves[valvesNum].flow);
            
            strcpy(pathsStr, &line.c_str()[line.find_first_of(';') + 24]);

            string paths = pathsStr;
            paths.erase(std::remove(paths.begin(), paths.end(), ' '), paths.end());

            uint32_t sep = 0;
            for (uint32_t i = 0; i < paths.length(); i++)
            {
                if (paths[i] == ',')
                {
                    strcpy(valves[valvesNum].ids[valves[valvesNum].idsNum], paths.substr(sep, i - sep).c_str());
                    valves[valvesNum].idsNum++;
                    sep = i + 1;
                }
            }

            strcpy(valves[valvesNum].ids[valves[valvesNum].idsNum], paths.substr(sep, paths.length() - sep).c_str());
            valves[valvesNum].idsNum++;

            valvesNum++;
        }
        else
        {
            break;
        }
    }

    for (uint64_t i = 0; i < valvesNum; i++)
    {
        flows.push_back(valves[i].flow);

        vector<uint64_t> v;
        for (uint64_t j = 0; j < valves[i].idsNum; j++)
        {
            v.push_back(getValveNum(valves[i].ids[j]));
        }
        connections.push_back(v);

        if (strcmp(valves[i].id, "AA") == 0)
        {
            AA = i;
        }
    }

    //part 1
    /*
    iter_t iter = { AA, 0, 30 , 0};
    uint64_t result = checkValve(iter);

    printf("%llu", result);
    */
    //part 2

    iter_t iterElefant = { AA, 0, 30 , 0 };
    checkValve(iterElefant);

    iter_t iter = { AA, 0, 26 , 1 };
    uint64_t result = checkValve(iter);

    printf("%llu", result);
}

uint64_t checkValve(iter_t iter)
{
    if (iter.timeLeft == 0)
    {
        if (iter.person == 0)
        {
            return 0;
        }
        else
        {
            iter_t iterNext = { AA, iter.doneReg, 26, 0 };
            return checkValve(iterNext);
        }
        
    }

    ITER_T iterMapRef = make_tuple(iter.valve, iter.doneReg, iter.timeLeft, iter.person);

    if (results.count(iterMapRef) >= 1)
    {
        return results[iterMapRef];
    }

    uint64_t num = 0;

    if (flows[iter.valve] != 0 && ((iter.doneReg & (1ULL << iter.valve)) == 0))
    {
        iter_t iterNext = { iter.valve, iter.doneReg | (1ULL << iter.valve), iter.timeLeft - 1, iter.person};
        num = flows[iter.valve] * (iter.timeLeft - 1) + checkValve(iterNext);
    }

    for (uint32_t con : connections[iter.valve])
    {
        iter_t iterNext = { con, iter.doneReg, iter.timeLeft - 1 , iter.person};
        num = max(num, checkValve(iterNext));
    }

    results[iterMapRef] = num;

    return num;
}

uint64_t getValveNum(char* id)
{
    for (uint64_t i = 0; i < valvesNum; i++)
    {
        if (strcmp(id, valves[i].id) == 0)
        {
            return i;
        }
    }

    printf("Not found");
    return 0;
}
