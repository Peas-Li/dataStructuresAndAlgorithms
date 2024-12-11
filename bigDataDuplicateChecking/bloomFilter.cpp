#include "../hash/stringHashFunc.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * Bloom Filter是通过一个位数组+k个哈希函数构成的。
 * 
 * Bloom Filter增加元素的过程:
 *  把元素的值通过k个哈希函数进行计算，得到k个值，然后把k当作位数组的下标，在位数组中把相应k个值修改成1。
 * 
 * Bloom Filter查询元素的过程:
 *  把元素的值通过k个哈希函数进行计算，得到k个值，然后把k当作位数组的下标，看看相应位数组下标标识的值是否全部是1，
 *  如果有一个为0，表示元素不存在(判断不存在绝对正确);
 *  如果都为1，表示元素存在(判断存在有错误率)
 * 
 * Bloom Filter的查找错误率，和位数组的大小，以及哈希函数的个数有关系，具体的错误率计算有相应的公式(错误率公式的掌握看个人理解，不做要求)。
 * Bloom Filter默认只支持add增加和query查询操作，不支持delete删除操作(因为存储的状态位有可能也是其它数据的状态位，删除后导致其它元素查找判断出错)。
 */

class bloomFilter
{
  public:
    bloomFilter(int size = 1471)

        : bitSize_(size)
    {
        bitMap_.resize(bitSize_ / 32 + 1);
    }

  public:
    void setBit(const char *str)
    {
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = RSHash(str) % bitSize_;
        int idx3 = APHash(str) % bitSize_;

        bitMap_[idx1 / 32] |= (1 << (idx1 % 32));
        bitMap_[idx2 / 32] |= (1 << (idx2 % 32));
        bitMap_[idx3 / 32] |= (1 << (idx3 % 32));
    }

    bool getBit(const char *str)
    {
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = RSHash(str) % bitSize_;
        int idx3 = APHash(str) % bitSize_;

        return  bitMap_[idx1 / 32] & (1 << (idx1 % 32)) &&
                bitMap_[idx2 / 32] & (1 << (idx2 % 32)) &&
                bitMap_[idx3 / 32] & (1 << (idx3 % 32))
                ? true : false;
    }

  private:
    int bitSize_;
    vector<int> bitMap_;
};

class blackList
{
  public:
    void add(string url)
    {
        blockList_.setBit(url.c_str());
    }

    bool query(string url)
    {
        return blockList_.getBit(url.c_str());
    }

  private:
    bloomFilter blockList_;
};

int main()
{
    blackList list;
    list.add("http://www.baidu.com");
    list.add("http://www.360buy.com");
    list.add("http://www.tmall.com");
    list.add("http://www.tencent.com");
    string url1 = "http://www.tencent.com";
    cout << list.query(url1) << endl;
    string url2 = "http://www.666.com";
    cout << list.query(url2) << endl;
}
