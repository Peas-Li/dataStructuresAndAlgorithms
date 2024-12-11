#include <iostream>

using namespace std;

void adjustArray(int a[], int size)
{
    int *front = a;
    int *second = a + size - 1;
    while(front < second)
    {
        while(*front % 2 == 0 && front < second)
            front++;
        while(*second % 2 == 1 && front < second)
            second--;
        if(front < second)
        {
            int tmp;
            tmp = *front;
            *front = *second;
            *second = tmp;
        }
    }

    return;
}

int main()
{
    int s[10];

    srand(static_cast<unsigned int>(time(NULL)));

    for(int i = 0; i < 10; i++)
    {
        s[i] = rand() % 100;
    }

    adjustArray(s, 10);

    for(int i = 0; i < 10; i++)
    {
        cout << s[i] << " ";
    }

    cout << endl;

    return 0;
}