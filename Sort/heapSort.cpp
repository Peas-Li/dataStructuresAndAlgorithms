#include "sort.h"

namespace mySort
{
    void push_heap(int arr[], int hole, int top, int val)
    {
        int parent = (hole - 1) / 2;
        while(hole > top && arr[parent] < val)
        {
            arr[hole] = arr[parent];
            hole = parent;
            parent = (hole - 1) / 2;
        }
        arr[hole] = val;
    }

    void pop_heap(int arr[], int hole, int len, int val)
    {
        int top = hole;
        int right = hole * 2 + 2;
        while(right < len)
        {
            if(arr[right - 1] > arr[right])
                --right;
            arr[hole] = arr[right];
            hole = right;
            right = hole * 2 + 2;
        }
        if(right == len)
        {
            arr[hole] = arr[right - 1];
            hole = right - 1;
        }
        arr[hole] = val;
        push_heap(arr, hole, top, val);
    }

    void make_heap(int arr[], int len)
    {
        int hole = (len - 2) / 2;
        while(hole >= 0)
        {
            pop_heap(arr, hole, len, arr[hole]);
            hole--;
        }
    }

    void heapSort(int arr[], int len)
    {
        make_heap(arr, len);
        while(len--)
        {
            int val = arr[len];
            arr[len] = arr[0];
            pop_heap(arr, 0, len, val);
        }
    }
}