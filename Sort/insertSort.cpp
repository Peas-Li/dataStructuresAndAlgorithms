#include "sort.h"

namespace mySort{
    void insertSort(int arr[], int len)
    {
        int i, j, val;
        for(i = 1; i < len; i++)
        {
            val = arr[i];
            for(j = i - 1; j >= 0; j--)
            {
                if(arr[j] > val)
                {
                    arr[j + 1] = arr[j];
                }
                else
                {
                    break;
                }
            }
            arr[j + 1] = val;
        }
    }
}