#include "sort.h"
#include <list>
#include <string>

namespace mySort
{
    void radixSort(int arr[], int len)
    {
        int max = abs(arr[0]);
        list<int> bucket[20];
        int numlen = 0;
        int k = 10;

        for(int i = 1; i < len; i++)
        {
            if(max < abs(arr[i]))
                max = arr[i];
        }
        
        numlen = to_string(max).size();
        while(numlen--)
        {
            for(int i = 0; i < len; i++)
            {
                bucket[(arr[i]%k)/(k/10) + 10].push_back(arr[i]);
            }
            for(int i = 0, j = 0; i < len; i++)
            {
                while(bucket[j].empty())   j++;
                arr[i] = bucket[j].front();
                bucket[j].pop_front();
            }
            k *= 10;
        }
    }
}