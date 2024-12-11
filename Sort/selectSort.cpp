#include "sort.h"

namespace mySort{
    void selectSort(int arr[], int len)
    {
        int minIndex = 0, i, j;
        for(i = 0; i < len - 1; i++)
        {
            minIndex = i;
            for(j = i + 1; j < len; j++)
            {
                if(arr[j] < arr[minIndex])
                {
                    minIndex = j;
                }
            }
            if(minIndex != i)
            {
                int tmp = arr[i];
                arr[i] = arr[minIndex];
                arr[minIndex] = tmp;
            }
        }
    }
}