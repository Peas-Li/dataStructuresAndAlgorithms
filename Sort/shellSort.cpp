#include "sort.h"

using namespace std;
namespace mySort
{
    void shellSort(int arr[], int len)
    {
        int gap = len / 2;
        int i, j, val;
        while(gap)
        {
            for(i = gap; i < len; i += gap)
            {
                val = arr[i];
                for(j = i - gap ; j >= 0; j -= gap)
                {
                    if(arr[j] > val)
                    {
                        arr[j + gap] = arr[j];
                    }
                    else
                    {
                        break;
                    }
                }
                arr[j + gap] = val;
            }
            gap /= 2;
        }
    }
}