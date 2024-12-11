#include <iostream>

using namespace std;

//时间复杂度是二叉树的高度，二叉树的高度是log2(n+1)

int binarySearch(int arr[], int i, int j, int val)
{
    if(i > j)   return -1;
    int mid = (i + j) / 2;
    if(arr[mid] == val)    return mid;
    else if(arr[mid] < val)    return binarySearch(arr, mid + 1, j , val);
    else    return binarySearch(arr, i, mid - 1 , val);
}

/*
int binarySearch(int arr[], int val)
{
    int len = nums.size();
    int i = 0;
    int j = len - 1;
    int mid = (j + i) / 2;
    while (j >= i)
    {
        if(nums[mid] == target)
        {
            return mid;
        }
        else if(nums[mid] < target)
        {
            i = mid + 1;
        }
        else
        {
            j = mid - 1;
        }
        mid = (i + j) / 2;
    }
    
    return -1;
}
*/

int main()
{
    int arr[10] = {2, 5, 78, 112, 466, 654, 754, 954, 1112, 21111};
    cout << binarySearch(arr, 0, 9, 21111) << endl;
    cout << binarySearch(arr, 0, 9, 78) << endl;
    cout << binarySearch(arr, 0, 9, 2) << endl;
    cout << binarySearch(arr, 0, 9, 100) << endl;
}