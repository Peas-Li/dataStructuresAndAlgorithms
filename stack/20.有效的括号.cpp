/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */
// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        stack<char> k;
        auto j = s.end(), i = s.begin();
        for(; i != j; i++)
        {
            switch(*i)
            {
                case '(':
                case '[':
                case '{':
                    k.push(*i);
                    break;
                case ')':
                    if(k.empty() || k.top() != '(') return false;
                    k.pop();
                    break;
                case ']':
                    if(k.empty() || k.top() != '[') return false;
                    k.pop();
                    break;
                case '}':
                    if(k.empty() || k.top() != '{') return false;
                    k.pop();
                    break;
                default:
                    break;
            }
        };
        
        return k.empty();
    }
};
// @lc code=end

/*
使用hash_map扩展性更高，不需要if-else或者switch判断，后续增加其他种类的
括号也可以直接采用，不需要增删语句
class Solution {
public:
    bool isValid(string s) {
        int n = s.size();
        if (n % 2 == 1) {
            return false;
        }

        unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };
        stack<char> stk;
        for (char ch: s) {
            if (pairs.count(ch)) {
                if (stk.empty() || stk.top() != pairs[ch]) {
                    return false;
                }
                stk.pop();
            }
            else {
                stk.push(ch);
            }
        }
        return stk.empty();
    }
};
*/

