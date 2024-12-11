#include <iostream>

using namespace std;

class seqStack
{
    private:
        int* mpStack;
        int mtop;
        int mcap;

    public:
        seqStack(int size = 10)
            : mtop(0)
            , mcap(size)
        {
            mpStack = new int[mcap];
        }

        ~seqStack()
        {
            delete [] mpStack;
            mpStack = nullptr;
        }

        void push(int val)
        {
            if(mtop == mcap)
                expand(mcap * 1.5);
            mpStack[mtop++] = val;
        }

        void pop()
        {
            if(mtop == 0)
                throw "stack is empty!";
            mtop--;
        }

        int& top() const
        {
            if(mtop == 0)
                throw "stack is empty!";
            return mpStack[mtop - 1];
        }

        bool empty() const
        {
            return mtop == 0;
        }

        int size() const
        {
            return mtop;
        }

    private:
        void expand(int size)
        {
            int* temp = new int[size];
            memcpy(temp, mpStack, mtop * sizeof(int));
            delete [] mpStack;
            mpStack = temp;
            mcap = size;
        }

};

int main()
{
    int arr[] = {12, 5, 46, 95, 48, 325, 56};
    seqStack s;

    for(auto v : arr)
        s.push(v);

    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.push(100);
    cout << s.top() << endl;
    cout << s.size() << endl;
    cout << s.empty() << endl;

    while(!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    cout << s.top() << endl;

    return 0;
}