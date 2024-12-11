#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <memory>

using namespace std;

/**
 * 比使用 hash 方法，内存小很多倍
 * 
 * 步骤：
 *  1、初始化 int 位图数组为： 数据量 / 32， 因为 int 占 4 字节，即32 位，每一位都可以表示一个数字是否存在，0 为不存在，反之存在
 *  2、每个二进制位对应一个整数值的状态（存在与否）。
 *  3、如果某个位是 1，表示该数字存在；如果是 0，表示该数字不存在。
 * 
 * 缺点一：
 *  不能查找谁是第一个不重复的，也不能查找重复了多少次
 *  解决办法：可以用两个位保存数据的状态，只有一次出现的，该数字所占用的位只能是01，但最大重复次数只能为3（11），
 *      调整位数灵活处理问题
 * 缺点二：
 *  数据：1 3 1000000000
 *  需要 new int[1000000000 / 32 + 1] 约30M，不如使用 hash
 *  解决办法：数据的个数和序列里面数字的最大值相当时使用
 */

int main()
{
    vector<int> vec;
    srand(time(NULL));
    for(int i = 0; i < 10000; i++)
    {
        vec.push_back(rand() % 10000);
    }

    int max = INT_MIN;
    for(int i : vec)
    {
        if(i > max) max = i;
    }

    //找出第一个重复的数字
    unique_ptr<int> bitMap1(new int[max / 32 + 1]());
    for(int i : vec)
    {
        int idx = i / 32;
        int offset = i % 32;
        if(*(bitMap1.get() + idx) & (1 << offset))
        {
            cout << "第一个重复的数字：" << i << endl;
            break;
        }
        *(bitMap1.get() + idx) |= (1 << offset); 
    }
}