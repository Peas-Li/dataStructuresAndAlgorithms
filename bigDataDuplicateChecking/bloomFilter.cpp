#include "../hash/stringHashFunc.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * Bloom Filter��ͨ��һ��λ����+k����ϣ�������ɵġ�
 * 
 * Bloom Filter����Ԫ�صĹ���:
 *  ��Ԫ�ص�ֵͨ��k����ϣ�������м��㣬�õ�k��ֵ��Ȼ���k����λ������±꣬��λ�����а���Ӧk��ֵ�޸ĳ�1��
 * 
 * Bloom Filter��ѯԪ�صĹ���:
 *  ��Ԫ�ص�ֵͨ��k����ϣ�������м��㣬�õ�k��ֵ��Ȼ���k����λ������±꣬������Ӧλ�����±��ʶ��ֵ�Ƿ�ȫ����1��
 *  �����һ��Ϊ0����ʾԪ�ز�����(�жϲ����ھ�����ȷ);
 *  �����Ϊ1����ʾԪ�ش���(�жϴ����д�����)
 * 
 * Bloom Filter�Ĳ��Ҵ����ʣ���λ����Ĵ�С���Լ���ϣ�����ĸ����й�ϵ������Ĵ����ʼ�������Ӧ�Ĺ�ʽ(�����ʹ�ʽ�����տ�������⣬����Ҫ��)��
 * Bloom FilterĬ��ֻ֧��add���Ӻ�query��ѯ��������֧��deleteɾ������(��Ϊ�洢��״̬λ�п���Ҳ���������ݵ�״̬λ��ɾ����������Ԫ�ز����жϳ���)��
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
