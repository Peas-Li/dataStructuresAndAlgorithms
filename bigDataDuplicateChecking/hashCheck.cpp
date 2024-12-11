#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdlib.h>
#include <time.h>

/**
 * 查询效率高，但内存占用随数据量的增大而增大
 */

using namespace std;

int main()
{
    vector<int> vec;
    srand(time(NULL));
    for(int i = 0; i < 10000; i++)
    {
        vec.push_back(rand() % 10000);
    }

    //第一次重复出现的数字
    unordered_set<int> us1;
    for(auto key : vec)
    {
        auto it = us1.find(key);
        if(it == us1.end())
        {
            us1.insert(key);
        }
        else
        {
            cout << "First: " << key << endl;
            break;
        }
    }

    //统计重复数字以及出现的次数
    unordered_map<int, int> um1;
    for(int key : vec)
    {
        /*auto it = um1.find(key);
        if(it == um1.end())
        {
            um1.emplace(key, 1);
        }
        else
        {
            it->second++;
        }*/
        um1[key]++;
    }

    for(auto pair : um1)
    {
        if(pair.second > 1)
        {
            cout << "Key: " << pair.first << " cnf: " << pair.second << endl;
        }
    }

    //去重，每个数字仅出现一次
    unordered_set<int> us2;
    for(auto i = vec.begin(); i != vec.end();)
    {
        auto it = us2.find(*i);
        if(it == us2.end())
        {
            us2.insert(*i);
            i++;
        }
        else
        {
            i = vec.erase(i);
        }
    }

    unordered_map<int, int> um2;
    int flag = 0;
    for(int key : vec)
    {
        um2[key]++;
    }

    for(auto pair : um2)
    {
        if(pair.second > 1)
        {
            flag = 1;
            break;
        }
    }

    if(!flag)   cout << "没有重复的数字了！" << endl;
    else        cout << "还有重复的数字！" << endl;
}