#include "sort.h"

namespace mySort
{   
    void mergeSortBuff(int arr[], int first, int last, int buff[])
    {
        if(!(first < last))
            return;
        int mid = (first + last) / 2;
        mergeSortBuff(arr, first, mid, buff);
        mergeSortBuff(arr, mid + 1, last, buff);

        if(arr[mid] < arr[mid + 1])
            return;

        int left1 = first, right1 = mid;
        int left2 = mid + 1, right2 = last;
        int i = 0;
        
        while(left1 <= right1 && left2 <= right2)
        {
            if(arr[left1] <= arr[left2])
                buff[i++]= arr[left1++];
            else
                buff[i++]= arr[left2++];
        }
        /*
        if(left1 <= right1)
        {
            for(; right1 >= left1; --right1)
                arr[last--] = arr[right1];
        }
        */
        if(left1 <= right1)
        {
            for(; right1 >= left1; ++left1)
                buff[i++] = arr[left1];
        }
        if(left2 <= right2)
        {
            for(; right2 >= left2; ++left2)
                buff[i++] = arr[left2];
        }
        for(int k = 0; k < i; k++)
            arr[first++] = buff[k];
        
    }

    void mergeSortBuff(int arr[], int len)
    {
        int* buff = new int[len];
        mergeSortBuff(arr, 0, len - 1, buff);
        delete [] buff;
    }
}