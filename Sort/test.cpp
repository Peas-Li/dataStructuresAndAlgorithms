#include <iostream>
#include <algorithm>
#include "sort.h"

void testSort()
{
    srand(static_cast<unsigned int>(time(NULL)));
    
    int len = rand() % 25 + 1;
    int arr[len];
    for(int i = 0; i < len; i++)
    {
        arr[i] = rand() % 1000;
        if(rand() % 2) arr[i] -= 2 * arr[i];
        cout << arr[i] << ' ';
    }
    cout << endl; 
    //int arr1[6] = {12,2,58,8,73,7 };
    //int arr1[3] = {-18, -194,  -96 };
    mySort::radixSort(arr, len);

    for(auto v : arr)
        cout << v << ' ';
    cout << endl;
}

void testPer()
{
    srand(static_cast<unsigned int>(time(NULL)));
    static const int LEN = 10000000; 
    int *arr1 = new int[LEN];
    int *arr2 = new int[LEN];
    int *arr3 = new int[LEN];
    int *arr4 = new int[LEN];
    for(int i = 0; i < LEN; i++)
    {
        int val = rand() % LEN;
        arr1[i] = val;
        arr2[i] = val;
        arr3[i] = val;
        arr4[i] = val;
    }
    clock_t beginTime, endTime;

    //beginTime = clock();
    //mySort::shellSort(arr1, LEN);
    //endTime = clock();
    //cout << "shellSort Time: " << (endTime - beginTime) * 1.0 / CLOCKS_PER_SEC << " s." << endl;
    
    beginTime = clock();
    mySort::quickSort(arr2, LEN);
    endTime = clock();
    cout << "quickSort Time: " << (endTime - beginTime) * 1.0 / CLOCKS_PER_SEC << " s." << endl;

    beginTime = clock();
    mySort::mergeSortBuff(arr3, LEN);
    endTime = clock();
    cout << "mergeSortBuff Time: " << (endTime - beginTime) * 1.0 / CLOCKS_PER_SEC << " s." << endl;

    beginTime = clock();
    mySort::heapSort(arr4, LEN);
    endTime = clock();
    cout << "heapSort Time: " << (endTime - beginTime) * 1.0 / CLOCKS_PER_SEC << " s." << endl;
}

int main()
{
    testSort();
    //testPer();
}