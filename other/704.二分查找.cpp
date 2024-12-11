/*
 * @lc app=leetcode.cn id=704 lang=cpp
 *
 * [704] 二分查找
 * 左闭右开区间，闭区间的查找看该目录下的 binarySearch
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int len = nums.size();
        int k = 0;
        int i = 0;
        int j = 0;
        while(len > 0)
        {
            k = len >> 1;
            j = i + k;
            if(nums[j] < target)
            {
                i = j + 1;
                len = len - k - 1;
            }
            else if(nums[j] > target)
            {
                len = k;
            }
            else
            {
                return j;
            }
        }
        return -1;
    }
};
// @lc code=end

