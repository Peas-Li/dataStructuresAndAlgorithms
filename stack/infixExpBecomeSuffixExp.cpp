#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<signed char, int> pairs = {
    {')', 0}, {'(', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}
};

int main()
{
    string str;
    string result;

    stack<char> s;

    while (getline(cin, str))
    {
        result.erase();
        for (auto ch : str)
        {
            if (ch >= '0' && ch <= '9')
                result = result + ch + ' ';
            else
            {
                if (ch == '(' || s.empty())
                    s.push(ch);
                else if (ch == ')')
                {
                    while (s.top() != '(' && !s.empty())
                    {
                        result = result + s.top() + ' ';
                        s.pop();
                    }
                    if (s.top() == '(')
                        s.pop();
                }
                else
                {
                    if (pairs.at(ch) > pairs.at(s.top()))
                        s.push(ch);
                    else
                    {
                        while (!s.empty() && pairs.at(ch) <= pairs.at(s.top()))
                        {
                            result = result + s.top() + ' ';
                            s.pop();
                        }
                        s.push(ch);
                    }
                }
            }
        }

        while (!s.empty())
        {
            result = result + s.top() + ' ';
            s.pop();
        }

        cout << result << endl;
    }

    return 0;
}