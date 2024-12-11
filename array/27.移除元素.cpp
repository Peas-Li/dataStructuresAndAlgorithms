/*
 * @lc app=leetcode.cn id=27 lang=cpp
 *
 * [27] 移除元素
 */

#include <vector>
// @lc code=start
class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        if(nums.empty()) return 0;
        auto front = nums.begin();
        auto second = nums.end() - 1;
        while(front < second)
        {
            while(*front != val && front < second)
                front++;
            while(*second == val && front < second)
                second--;
            if(front < second)
            {
                *front = *second;
                second--;
            }
        }
        
        if(*front != val)
            front++;

        return front - nums.begin();
    }
};
// @lc code=end

/*
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int left = 0;
        for (int right = 0; right < n; right++) {
            if (nums[right] != val) {
                nums[left] = nums[right];
                left++;
            }
        }
        return left;
    }
};
 */

/*
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size();
        while (left < right) {
            if (nums[left] == val) {
                nums[left] = nums[right - 1];
                right--;
            } else {
                left++;
            }
        }
        return left;
    }
};
与方法一不同的是，方法二避免了需要保留的元素的重复赋值操作。
*/