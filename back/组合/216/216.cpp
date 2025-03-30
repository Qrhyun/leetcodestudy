#include <iostream>
#include <vector>
using namespace std;
class Solution
{
private:
  vector<vector<int>> result; // 存放符合条件结果的集合
  vector<int> path;           // 用来存放符合条件结果.方便后面判断长度到达后，把path加入到result中
  void backtracking(int targetSum, int k, int sum, int startIndex)
  {
    // 终止条件
    if (path.size() == k)
    {
      if (sum == targetSum)
        result.push_back(path);
      return;
    }
    // 回溯和递归
    for (int i = startIndex; i <= 9; i++)
    {
      sum += i;
      path.push_back(i);
      backtracking(targetSum, k, sum, i + 1); // 注意i+1调整startIndex
      sum -= i;                               // 回溯
      path.pop_back();                        // 回溯
      // 注意这里的回溯，sum也要回溯
    }
  }

public:
  vector<vector<int>> combinationSum3(int k, int n)
  {
    result.clear();
    path.clear();
    backtracking(n, k, 0, 1); // sum先置为0，从1开始
    return result;
  }
};
/*
剪枝有两处地方
1.sum已经大于了targetSum，那么后面就没有必要遍历了
//已选元素总和如果已经大于n（图中数值为4）了，那么往后遍历就没有意义了，直接剪掉。
//剪枝的地方可以放在递归函数开始的地方
if (sum > targetSum) { // 剪枝操作
    return;
}
2.和普通组合问题一样，for循环也可以剪枝，如果后序遍历的元素个数已经不够k了，那么就没有必要遍历了
 for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++)
class Solution {
private:
    vector<vector<int>> result; // 存放结果集
    vector<int> path; // 符合条件的结果
    void backtracking(int targetSum, int k, int sum, int startIndex) {
        if (sum > targetSum) { // 剪枝操作
            return;
        }
        if (path.size() == k) {
            if (sum == targetSum) result.push_back(path);
            return; // 如果path.size() == k 但sum != targetSum 直接返回
        }
        for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) { // 剪枝
            sum += i; // 处理
            path.push_back(i); // 处理
            backtracking(targetSum, k, sum, i + 1); // 注意i+1调整startIndex
            sum -= i; // 回溯
            path.pop_back(); // 回溯
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        result.clear(); // 可以不加
        path.clear();   // 可以不加
        backtracking(n, k, 0, 1);
        return result;
    }
};


*/