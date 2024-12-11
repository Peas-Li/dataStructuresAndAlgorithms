#include <iostream>
#include <vector>

using namespace std;

/**
 * 快排分割 topK 问题的时间复杂度：O(n) ~ O(n^2)
 * 可以优化，其优化方法就是对快速排序的优化...
 */

void quickSort(int arr[], int first, int last, int k)
{
    if(!(first < last))
        return;
    int base = arr[first];
    int left = first, right = last;
    while(left < right)
    {
        while(left < right && arr[right] >= base) right--;
        if(left < right)
            arr[left++] = arr[right];
        while(left < right && arr[left] <= base) left++;
        if(left < right)
            arr[right--] = arr[left];
    }
    arr[left] = base;
    if(left + 1 == k)   return;
    if(left + 1 > k)    quickSort(arr, first, left - 1, k);
    if(left + 1 < k)    quickSort(arr, left + 1, last, k);
}

void topK(int arr[], int len, int k)
{
    quickSort(arr, 0, len - 1, k);
}

int main()
{
    static const int LEN = 1000;
    int *arr = new int[LEN];
    srand(time(NULL));
    for(int i = 0; i < LEN; i++)
    {
        arr[i] = rand() % LEN;
    }

    int k = 3;
    topK(arr, LEN, k);

    for(int i = 0; i < k; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}