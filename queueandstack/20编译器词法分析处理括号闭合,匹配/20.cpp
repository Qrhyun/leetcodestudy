//三种情况左方向的括号多余了，右方向的括号多余了，括号没有多余，但是 括号的类型没有匹配上
//用栈
#include <iostream>
#include <string>
#include <stack>//栈,STL容器适配器
using namespace std;
class Solution {
public:
    bool isValid(string s) {
        if(s.size()%2==1){
            //因为栈的内部实现是数组容器，所以可以用size()函数
            return false;
        }
        stack<char> st;//创建一个栈,用于存放进入的括号
        for(int i=0;i<s.size();i++){
            //1.左括号入栈，入的是对应的右括号
            if(s[i]=='('){
                st.push(')');
            }
            else if(s[i]=='['){
                st.push(']');
            }
            else if(s[i]=='{'){
                st.push('}'); 
            }
            //2.右括号检验，促使左括号出栈
            else if(st.empty()||st.top()!=s[i]){
               return false; 
            }
            else{
                st.pop();
            }
    }
    return st.empty();//巧妙的运用了empty()函数
}
};