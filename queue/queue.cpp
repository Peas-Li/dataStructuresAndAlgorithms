#include <iostream>
#include <memory.h>

using namespace std;

class queue
{
    private:
        int* pQue_;
        int cap_;
        int front_;
        int rear_;
        int size_;

    public:
        queue(int size = 10)
            : cap_(size)
            , front_(0)
            , rear_(0)
            , size_(0)
        {
            pQue_ = new int[cap_];
        }

        ~queue()
        {
            delete [] pQue_;
            pQue_ = nullptr;
        }

        void push(int val)
        {
            if((rear_ + 1) % cap_ == front_)
                expand(cap_ * 1.5);
            pQue_[rear_] = val;
            rear_ = (rear_ + 1) % cap_;
            size_++;
        }

        void pop()
        {
            if(empty())
                throw "queue is empty!";
            front_ = (front_ + 1) % cap_;
            size_--;
        }

        int front() const
        {
            if(empty())
                throw "queue is empty!";
            return pQue_[front_];
        }

        int back() const
        {
            if(empty())
                throw "queue is empty!";
            return pQue_[(rear_ - 1 + cap_) % cap_];
        }

        bool empty() const
        {
            return rear_ == front_;
        }

        int size() const
        {
            return size_;
        }

        void show() const
        {
            for(int i = front_; i != rear_; i = (i + 1) % cap_)
            {
                cout << pQue_[i] << " ";
            }

            cout << endl;
        }

    private:
        void expand(int size)
        {
            int* newQueue = new int[size];
            for(int i = 0, j = front_; j != rear_; i++, j = (j + 1) % cap_)
            {
                newQueue[i] = pQue_[j];
            }
            delete [] pQue_;
            pQue_ = newQueue;
            front_ = 0;
            rear_ = cap_ - 1;
            cap_ = size;
        }   
};

int main()
{
    int arr[] = {12, 5, 46, 95, 48, 325, 56};
    queue que;

    for(auto v : arr)
        que.push(v);

    cout << que.front() << endl;;
    cout << que.back() << endl;
    que.show();

    que.pop();

    cout << que.front() << endl;;
    cout << que.back() << endl;
    que.show();

    que.push(100);
    que.push(100);
    que.push(100);
    que.push(100);
    que.push(100);

    cout << que.front() << endl;;
    cout << que.back() << endl;
    que.show();

    cout << que.size() << endl;

    return 0;
}