//消除相同的元素，返回新的字符串
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>//reverse函数

using namespace std;
class Solution {
public:
    string remove(string s){
        //1.键栈
        stack<char> st;
        //2.遍历字符串,并执行消除操作
        for(int i=0;i<s.size();i++){
            if(st.empty()||s[i]!=st.top()){
                //这里要把st.empty()放在前面，否则会出现段错误，保证代码的健壮性
                st.push(s[i]);
            }
            else{
                st.pop();
            }
        
        }
        //3.将栈中的元素转换为字符串
        string result="";//std::string 是一个动态字符串类，初始化为 "" 表示它是一个空字符串。
        while(!st.empty()){
            //判断为空时候，用while比for循环好
            result += st.top();// std::string 支持使用 += 运算符来拼接字符或字符串。
            st.pop();
        }
        //4.反转字符串
        reverse(result.begin(),result.end());//begin() 和 end() 是 C++ 标准库容器（如 std::string, std::vector, std::deque 等）提供的成员函数，用于获取容器的迭代器范围。它们定义在 <string>、<vector> 等容器对应的头文件中。
        return result;
    }

};