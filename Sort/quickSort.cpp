#include "sort.h"

namespace mySort
{
    void quickSort(int arr[], int first, int last)
    {
        if(!(first < last))
            return;
        int tmp = arr[first];
        int left = first;
        int second = last;
        while(left < second)
        {
            while(left < second && arr[second] >= tmp)
                second--;

            if(left < second)
                arr[left++] = arr[second];

            while(left < second && arr[left] <= tmp)
                left++;    

            if(left < second)
                arr[second--] = arr[left];
        }
        arr[left] = tmp;
        quickSort(arr, first, left - 1);
        quickSort(arr, left + 1, last);
    }

    void quickSort(int arr[], int len)
    {
        quickSort(arr, 0, len - 1);
    }
}
