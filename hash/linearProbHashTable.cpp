#include <iostream>

using namespace std;

/**
 * 容易发生哈希冲突，靠近0(n)的时间复杂度，存储遍慢
 * 多线程环境中，线性探测所用到的基于数组实现的哈希表只能给全局的表用互斥锁来保证哈希表的原子操作，保证线程安全!
 * 
 * 散列函数设计特点：
 *  计算简单(复杂会降低查找的时间)
 *  散列地址分布均匀(减少哈希冲突)
 * 
 * 散列函数：
 *  直接定址法
 *  数字分析法
 *  平均取中法
 *  折叠法&随机数法
 *  除留余数法
 *  md5, sha加密hash算法等
 * 
 * 散列冲突处理
 *  线性探测
 *  二次探测
 *  链地址法
 */

enum State
{
    STATE_UNUSE,
    STATE_USING,
    STATE_DEL,
};


struct Hash
{
    Hash(int val = 0)
        : bucketSize(val)
    {}

    int bucketSize;
    int operator()(const int &val) const
    {
        return val % bucketSize;
    }
};


struct Bucket
{
    Bucket(int val = 0, State state = STATE_UNUSE)
        : Key_(val)
        , state_(state)
    {}

    int Key_;
    State state_;
};

class hashTable
{
    public:
        hashTable(int size = primes_[0], double loadFactor = 0.75)
            : useBucketNum_(0)
            , loadFactor_(loadFactor)
            , primeIdx_(0)
        {
            if(size > primes_[primeIdx_])
            {
                for(; primeIdx_ < PRIME_SIZE; primeIdx_++)
                {
                    if(primes_[primeIdx_] > size)
                    {
                        break;
                    }
                }
            }
            primeIdx_ = primeIdx_ == PRIME_SIZE ? --primeIdx_ : primeIdx_;
            tableSize_ = primes_[primeIdx_];
            table_ = new Bucket[tableSize_];
            hash_ = Hash(tableSize_);
        }

        ~hashTable()
        {
            delete [] table_;
            table_ = nullptr;
        }

    public:

        //鍙互閲嶅鎻掑叆
        void insert(int key)
        {
            if(float(useBucketNum_ + 1) > float(tableSize_ * loadFactor_))
                expand();

            int n = hash_(key);
            while(table_[n].state_ == STATE_USING) n = (n + 1) % tableSize_;
            table_[n].Key_ = key;
            table_[n].state_ = STATE_USING;
            useBucketNum_++;
        }

        void erase(int key)
        {
            int n = hash_(key);
            int bound = n;
            do
            {
                if(table_[n].Key_ == key && table_[n].state_ == STATE_USING)
                {
                    table_[n].state_ = STATE_DEL;
                    useBucketNum_--;
                }
                n = (n + 1) % tableSize_;
            }while(table_[n].state_ != STATE_UNUSE && n != bound);
        }

        bool find(int key) const
        {
            int n = hash_(key);
            int bound = n;
            do
            {
                if(table_[n].Key_ == key && table_[n].state_ == STATE_USING)
                    return true;

                n = (n + 1) % tableSize_;
            }while(table_[n].state_ != STATE_UNUSE && n != bound);

            return false;
        }

    private:
        void expand()
        {
            primeIdx_++;
            if(primeIdx_ == PRIME_SIZE)
                throw "hashTable is  too large, can not expand anymore!";
            hash_ = Hash(tableSize_);
            Bucket* newTable = new Bucket[primes_[primeIdx_]];
            for(int i = 0; i < tableSize_; i++)
            {
                if(table_[i].state_ == STATE_USING)
                {
                    int n = hash_(table_[i].Key_);
                    while(newTable[n].state_ == STATE_USING) n = (n + 1) % tableSize_;
                    newTable[n].Key_ = table_[i].Key_;
                    newTable[n].state_ = table_[i].state_;
                }
            }
            delete [] table_;
            table_ = newTable;
            tableSize_ = primes_[primeIdx_];
        }

    private:
        Bucket* table_;
        int tableSize_;
        int useBucketNum_;
        double loadFactor_;
        static const int PRIME_SIZE = 10;
        static int primes_[PRIME_SIZE];
        int primeIdx_;
        Hash hash_; 
};

int hashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main()
{
    hashTable htable;
    htable.insert(21);
    htable.insert(32);
    htable.insert(14);
    htable.insert(15);
    htable.insert(22);

    cout << htable.find(21) << endl;
    cout << htable.find(32) << endl;
    cout << htable.find(14) << endl;
    cout << htable.find(15) << endl;
    cout << htable.find(22) << endl;
    cout << htable.find(0) << endl;
    cout << htable.find(80) << endl;
    cout << htable.find(45) << endl;

    htable.erase(32);
    cout << htable.find(32) << endl;
    htable.erase(15);
    cout << htable.find(15) << endl;
}
