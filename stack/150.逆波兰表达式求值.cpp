/*
 * @lc app=leetcode.cn id=150 lang=cpp
 *
 * [150] 逆波兰表达式求值
 */

// @lc code=start
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        int r1;
        int r2;
        int val = 0;
        int len = 0;
        char k;
        int p;
        auto i = tokens.begin(), j = tokens.end();
        for(; i != j; i++)
        {   
            string &tmp = *i;
            k = tmp[0];
            len = tmp.length();
            if((k >= '0' && k <= '9') || (len > 1))
            {
                p = (k == '-') ? 1 : 0;
                for(; p != len; p++)
                {
                    val = val * 10 + tmp[p] - '0';
                }
                if(k == '-') 
                    s.push(-val);
                else
                    s.push(val);
                val = 0;
            }
            else
            {
                r1 = s.top();
                s.pop();
                r2 = s.top();
                s.pop();
                switch(k)
                {
                    case '+':
                        s.push(r2 + r1);
                        break;
                    case '-':
                        s.push(r2 - r1);
                        break;
                    case '*':
                        s.push(r2 * r1);
                        break;
                    case '/':
                        s.push(r2 / r1);
                        break;
                    default:
                        break;
                }
            }
        }

        return s.top();
    }
};
// @lc code=end

/*
isNumber(), Integer.parseInt()的熟练使用
atoi(token.c_str())的熟练使用

class Solution {
    public int evalRPN(String[] tokens) {
        Deque<Integer> stack = new LinkedList<Integer>();
        int n = tokens.length;
        for (int i = 0; i < n; i++) {
            String token = tokens[i];
            if (isNumber(token)) {
                stack.push(Integer.parseInt(token));
            } else {
                int num2 = stack.pop();
                int num1 = stack.pop();
                switch (token) {
                    case "+":
                        stack.push(num1 + num2);
                        break;
                    case "-":
                        stack.push(num1 - num2);
                        break;
                    case "*":
                        stack.push(num1 * num2);
                        break;
                    case "/":
                        stack.push(num1 / num2);
                        break;
                    default:
                }
            }
        }
        return stack.pop();
    }

    public boolean isNumber(String token) {
        return !("+".equals(token) || "-".equals(token) || "*".equals(token) || "/".equals(token));
    }
}
*/