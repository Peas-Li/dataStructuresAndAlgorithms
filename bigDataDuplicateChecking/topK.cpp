#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <functional>
#include <map>

using namespace std;

/**
 * topK 问题的时间复杂度：O(n) * O(logK) -> O(n)
 * 
 * 找最小的前 K 个元素：
 * 序列的前 K 个元素建立一个“大根堆”，依次遍历后续的值，只要比堆顶元素小，就取而代之，并调整堆，接着向后遍历；
 * 
 * 找最大的前 K 个元素：
 * 序列的前 K 个元素建立一个“小根堆”，依次遍历后续的值，只要比堆顶元素大，就取而代之，并调整堆，接着向后遍历；
 */

//int& int&
//const int& const int&
//const int& const int &

int main()
{
    vector<int> vec;
    static const int LEN = 10000;
    srand(time(NULL));
    for(int i = 0; i < LEN; i++)
    {
        vec.push_back(rand() % (LEN / 10));
    }

    int k = 5;
    //找前 K 个最小的元素，priority_queue 的底层实现是堆排序，默认是大根堆；
    priority_queue<int> maxHeap;

    for(int i = 0; i < LEN; i++)
    {
        if(i < k)
            maxHeap.push(vec[i]);
        else
        {
            if(vec[i] < maxHeap.top())
            {
                maxHeap.pop();
                maxHeap.push(vec[i]);
            }
        }
    }

    cout << "前 K 个最小的元素:" << endl;
    for(int i = 0; i < k; i++)
    {
        cout << maxHeap.top() << " ";
        maxHeap.pop();

    }
    cout << endl;

    //找前 K 个最大的元素
    priority_queue<int, vector<int>, std::greater<int>> minHeap;

    for(int i = 0; i < LEN; i++)
    {
        if(i < k)
            minHeap.push(vec[i]);
        else
        {
            if(vec[i] > minHeap.top())
            {
                minHeap.pop();
                minHeap.push(vec[i]);
            }
        }
    }

    cout << "前 K 个最大的元素:" << endl;
    for(int i = 0; i < k; i++)
    {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;

    //找前 K 个重复次数最小的元素
    using Type = pair<int, int>;
    using Comp = function<bool(Type&, Type&)>;
    unordered_map<int, int> mp;
    priority_queue<Type, vector<Type>, Comp> maxCountK(
        [](Type& a, Type& b)->bool
        {
            return a.second < b.second;
        }
    );

    for(int i = 0; i < LEN; i++)
    {
        mp[vec[i]]++;
    }

    auto it1 = mp.begin();
    for(int i = 0; i < k; i++)
    {
        maxCountK.push(*it1++);
    }

    for(; it1 != mp.end(); it1++)
    {
        if(it1->second < maxCountK.top().second)
        {
            maxCountK.pop();
            maxCountK.push(*it1);
        }
    }

    cout << "前 K 个重复次数最小的元素:" << endl;
    for(int i = 0; i < k; i++)
    {
        auto p = maxCountK.top();
        cout << p.first << ": 重复了 " << p.second << " 次" << endl;
        maxCountK.pop();
    }
    
    //找前 K 个重复次数最大的元素
    priority_queue<Type, vector<Type>, Comp> minCountK(
        [](Type& a, Type& b)->bool
        {
            return a.second > b.second;
        }
    );

    auto it2 = mp.begin();
    for(int i = 0; i < k; i++)
    {
        minCountK.push(*it2++);
    }

    for(; it2 != mp.end(); it2++)
    {
        if(it2->second > minCountK.top().second)
        {
            minCountK.pop();
            minCountK.push(*it2);
        }
    }

    cout << "前 K 个重复次数最大的元素:" << endl;
    for(int i = 0; i < k; i++)
    {
        auto p = minCountK.top(); 
        cout << p.first << ": 重复了 " << p.second << " 次" << endl;
        minCountK.pop();
    }
}