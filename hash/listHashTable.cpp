#include <iostream>
#include <vector>
#include <list>

using namespace std;

/**
 * 发生哈希冲突时，靠近O(n)的时间复杂度，存储遍慢了，但可以优化：
 *      当链表长度大于8(10)，把桶里面的这个链表转化成红黑树 O(logn)
 * 多线程环境中，段的锁使用既保证了线程安全，又有一定的并发量，提高了效率!
 */


struct Node
{
    Node() = default;
    Node(int val)
        : key_(val)
        , next_(nullptr)
    {}

    Node(const Node &node)
        : key_(node.key_)
        , next_(node.next_)
    {}

    Node(Node &&node)
        : key_(std::move(node.key_))
        , next_(node.next_)
    {
        node.next_ = nullptr;
    }

    int key_;
    Node *next_;
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


class listHashTable
{
    public:
        listHashTable(int size = primes_[0], double loadFactor = 0.75)
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
            table_.reserve(tableSize_);
            table_.assign(tableSize_, nullptr);
            hash_ = Hash(tableSize_);
        }

    public:

        //不可以重复插入
        void insert(int key)
        {
            if(float(useBucketNum_ + 1) > float(tableSize_ * loadFactor_))
                expand();
            
            int n = hash_(key);
            Node *cur = table_[n];
            for(Node *next = cur; next != nullptr; cur = next, next = next->next_)
            {
                if(next->key_ == key)   return;
            }
            Node *newNode = new Node(key);
            newNode->next_ = cur;
            table_[n] = newNode;
            useBucketNum_++;
        }

        void erase(int key)
        {
            int n = hash_(key);
            Node *cur = table_[n];
            if(cur == nullptr) return;
            if(cur->key_ == key)
            {
                table_[hash_(key)] = cur->next_;
                delete cur;
                return;
            }
            for(Node *next = cur; next != nullptr; cur = next, next = next->next_)
            {
                if(next->key_ == key)
                {
                    cur->next_ = next->next_;
                    delete next;
                    return;
                }
            }
        }

        bool find(int key)
        {
            int n = hash_(key);
            Node *cur = table_[n];
            for(; cur != nullptr; cur = cur->next_)
            {
                if(cur->key_ == key)
                {
                    return true;
                }
            }
            return false;
        }

    private:
        void expand()
        {
            primeIdx_++;
            if(primeIdx_ == PRIME_SIZE)
                throw "hashTable is  too large, can not expand anymore!";
            hash_ = Hash(primes_[primeIdx_]);
            vector<Node*> newTable(primes_[primeIdx_], nullptr);

            for(int i = 0; i < tableSize_; i++)
            {
                if(table_[i] == nullptr)    continue;
                for(Node *oldCur = table_[i]; oldCur != nullptr; oldCur = oldCur->next_)
                {
                    int n = hash_(oldCur->key_);
                    Node *cur = newTable[n];
                    Node *newNode = new Node(oldCur->key_);
                    newNode->next_ = cur;
                    newTable[n] = newNode;
                }
            }
            swap(table_, newTable);
            tableSize_ = primes_[primeIdx_];
        }

    private:
        vector<Node*> table_;
        int tableSize_;
        int useBucketNum_;
        double loadFactor_;
        static const int PRIME_SIZE = 10;
        static int primes_[PRIME_SIZE];
        int primeIdx_;
        Hash hash_; 
};

int listHashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main()
{
    listHashTable htable;
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
