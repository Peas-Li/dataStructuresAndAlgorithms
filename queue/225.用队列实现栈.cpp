/*
 * @lc app=leetcode.cn id=225 lang=cpp
 *
 * [225] 用队列实现栈
 */
#include <queue>

using namespace std;
// @lc code=start
class MyStack {
public:
public:
    MyStack(){

    }
    
    void push(int x) {
        s1.push(x);
    }
    
    /*
    标准解析：在push的时候，就直接反转元素；
    void push(int x) {
        int n = q.size();
        q.push(x);
        for (int i = 0; i < n; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    */

    int pop() {
        int len = s1.size() - 1;
        while(len--)
        {
            s1.push(s1.front());
            s1.pop();
        }
        int k = s1.front();
        s1.pop();
        return k;
    }
    
    int top() {
        int len = s1.size() - 1;
        while(len--)
        {
            s1.push(s1.front());
            s1.pop();
        }
        int k = s1.front();
        s1.push(s1.front());
        s1.pop();
        return k;
    }
    
    bool empty() {
        return s1.empty();
    }
private:
    queue<int> s1;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
// @lc code=end

/*
第一次实现，用了两个队列
class MyStack {
public:
public:
    MyStack(){

    }
    
    void push(int x) {
        s1.push(x);
    }
    
    int pop() {
        while(!s1.empty() && s1.size() != 1)
        {
            s2.push(s1.front());
            s1.pop();
        }
        int k = s1.front();
        s1.pop();
        while(!s2.empty())
        {
            s1.push(s2.front());
            s2.pop();
        }
        return k;
    }
    
    int top() {
        while(!s1.empty() && s1.size() != 1)
        {
            s2.push(s1.front());
            s1.pop();
        }
        int k = s1.front();
        s2.push(s1.front());
        s1.pop();
        while(!s2.empty())
        {
            s1.push(s2.front());
            s2.pop();
        }
        return k;
    }
    
    bool empty() {
        return s1.empty();
    }
private:
    queue<int> s1;
    queue<int> s2;
};
*/