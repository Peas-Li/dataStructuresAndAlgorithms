#include "sort.h"

namespace mySort{
    void bubblingSort(int arr[], int len)
    {
        for(int i = 0; i < len - 1; i++)//2、再写循环多少次
        {
            bool flag = false;
            for(int j = 0; j < len - 1 - i; j++) //1、先写核心：for(int j = 0; j < len - 1; j++)
            {                                    //3、最后修改边界：for(int j = 0; j < len - 1 - i; j++)
                if(arr[j] > arr[j + 1])
                {
                    int tmp = arr[j + 1];
                    arr[j + 1] = arr[j];
                    arr[j] = tmp;
                    flag = true;
                }
            }
            if(!flag)   return;
        }
    }
}
