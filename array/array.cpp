#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Array
{
    private:
        int *mpArr;
        int mCap;
        int mCur;

        void expand(int size)
        {
            int *tmp = new int[size];
            for(int i = 0; i < mCap; i++)
            {
                tmp[i] = mpArr[i];
            }
            delete []mpArr;
            mpArr = tmp;
            mCap = size;
        }

    public:
        Array(int size = 10) : mCap(size), mCur(0)
        {
            mpArr = new int[size];
        }

        ~Array()
        {
            delete []mpArr;
            mpArr = nullptr;
        }

        void push_back(int val)
        {
            if(mCur == mCap)
            {
                expand(mCap * 2);
            }
            mpArr[mCur++] = val;
        }

        void pop_back()
        {
            if(mCur == 0)
            {
                return;
            }
            mCur--;
        }

        void insert(int pos, int val)
        {
            if(pos < 0 || pos > mCur)
            {
                return;
            }
            if(mCur == mCap)
            {
                expand(mCap * 2);
            }
            int *p = mpArr + pos;
            for(int *q = mpArr + mCur; q != p; q--)
            {
                *q = *(q - 1);
            }
            *p = val;
            mCur++;
        }

        void erase(int pos)
        {
            if(pos >= mCur || pos < 0)
                return;
            for(int q = pos + 1; q < mCur; q++)
            {
                mpArr[q - 1] = mpArr[q];
            }
            mCur--;
        }

        int find(int val)
        {
            for(int i = 0; i < mCur; i++)
            {
                if(mpArr[i] == val)
                {
                    return i;
                }
            }

            return -1;
        }

        void show()
        {
            for(int i = 0; i < mCur; i++)
            {
                cout << mpArr[i] << " ";
            }
            cout << endl;
        }
};

int main()
{
    Array arr;
    srand(static_cast<unsigned int>(time(NULL)));
    for(int i = 0; i < 10; i++)
    {
        arr.push_back(rand() % 100);
    }

    arr.show();
    arr.pop_back();
    arr.show();

    arr.insert(0, 100);
    arr.show();
    arr.insert(10, 200);
    arr.show();

    int pos = arr.find(100);
    if(pos != -1)
    {
        arr.erase(pos);
        arr.show();
    }

    return 0;
}