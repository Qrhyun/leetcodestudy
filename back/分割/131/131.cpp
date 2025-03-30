/*
切割问题类似组合问题。
例如对于字符串abcdef：
组合问题：选取一个a之后，在bcdef中再去选取第二个，选取b之后在cdef中再选取第三个.....。
切割问题：切割一个a之后，在bcdef中再去切割第二段，切割b之后在cdef中再切割第三段.....。
在处理组合问题的时候，递归参数需要传入startIndex，表示下一轮递归遍历的起始位这个startIndex就是切割线。
终止条件：
切割线达到了字符串的末尾，说明找到了一组切割方法。
在处理切割问题的时候，递归参数需要传入一个int型的startIndex，表示下一轮递归遍历的起始位置，这个startIndex就是切割线。
在for (int i = startIndex; i < s.size(); i++)循环中，我们 定义了起始位置startIndex，那么 [startIndex, i] 就是要截取的子串。
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Solution
{
private:
  // 函数1：判断是否是回文子串.双指针法
  bool isPalindrome(const string &s, int start, int end)
  {
    for (int i = start, j = end; i < j; i++, j--)
    {
      if (s[i] != s[j])
        return false;
    }
    return true;
  }
  vector<vector<string>> result;
  vector<string> path; // 放已经回文的子串
  // 1.确定递归函数的参数和返回值
  void backtracking(const string &s, int startIndex)
  {
    // 2.终止条件
    if (startIndex >= s.size())
    {
      result.push_back(path);
      return;
    }
    // 3.单层递归逻辑
    for (int i = startIndex; i < s.size(); i++)
    {
      // 是回文子串
      if (isPalindrome(s, startIndex, i))
      {
        // 这里借助i++来完成字符串[startIndex,i]的end尾指针的动态增长
        string str = s.substr(startIndex, i - startIndex + 1);
        // substr(startIndex,i-startIndex+1)是从startIndex开始，长度为i-startIndex+1的子串
        path.push_back(str);
      }
      else
      {
        continue; // 不是回文子串，直接跳过,继续下一个for循环
      }
      backtracking(s, i + 1); // 递归，注意这里的startIndex是i+1，因为要从下一个位置开始遍历.纵向的逻辑
      path.pop_back();        // 回溯过程，弹出本次已经填在的子串,PATH就是一个动态的
    }
  }

public:
  vector<vector<string>> partition(string s)
  {
    result.clear(); // 清空result，防止结果累积
    path.clear();   // 清空path，防止结果累积
    backtracking(s, 0);
    return result;
  }
};
