#include <iostream>
#include <functional>
#include <stdlib.h>
#include <time.h>

using namespace std;

class priorityQueue
{
    public:
        using Comp = function<bool(int, int)>;
        
        priorityQueue(Comp comp)
        : size_(0)
        , cap_(20)
        , comp_(comp)
        {
            que_ = new int[cap_];
        }

        priorityQueue(int cap = 20, Comp comp = greater<int>())
        : size_(0)
        , cap_(cap)
        , comp_(comp)
        {
            que_ = new int[cap_];
        }

        ~priorityQueue()
        {
            delete [] que_;
        }

        void push(int val)
        {
            if(size_ == cap_)
            {
                int* p = new int[2 * cap_];
                memcpy(p, que_, cap_ * sizeof(int));
                delete [] que_;
                que_ = p;
                cap_ = 2 * cap_;
            }
            int index = size_;
            int parent = (index - 1) / 2;
            while(index > 0 && comp_(val, que_[parent]))
            {
                que_[index] = que_[parent];
                index = parent;
                parent = (parent - 1) / 2;
            }
            que_[index] = val;
            size_++;
        }

        void pop()
        {
            if(empty())
                throw "container is empty!";
            size_--;
            if(size_ == 0)  return;
            int val = que_[size_];
            int top = 0;
            while(top < size_ / 2)
            {
                int child =  2 * top + 1;
                if(child + 1 < size_ && comp_(que_[child + 1], que_[child]))
                    child += 1;
                if(comp_(que_[child], val))
                {
                    que_[top] = que_[child];
                    top = child;
                }
                else
                    break;
            }
            que_[top] = val;
        }

        int top()
        {
            if(size_ == 0) 
                throw "container is empty!";
            return que_[0];
        }

        bool empty()
        {
            return size_ == 0 ? true : false;
        }

    private:
        int* que_;
        int size_;
        int cap_;
        Comp comp_;
};

int main()
{
    priorityQueue que([](int a, int b){ return a < b; });
    srand(time(NULL));

    for(int i = 0; i < 10; i++)
    {
        int tmp = rand() % 100;
        cout << tmp <<  ' ';
        que.push(tmp);
    }
    cout << endl;

    while(!que.empty())
    {
        cout << que.top() << " ";
        que.pop();
    }

    cout << endl;
}