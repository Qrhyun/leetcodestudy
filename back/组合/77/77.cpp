#include <iostream>
#include <vector>
using namespace std;
class Solution
{
private:
  // 1.确定递归函数的参数和返回值

  vector<vector<int>> result; // 存放符合条件结果的集合
  vector<int> path;           // 用来存放符合条件结果.方便后面判断长度到达后，把path加入到result中
  void backtracking(int n, int k, int startIndex)
  {
    // int型变量startIndex，这个参数用来记录本层递归的中，集合从哪里开始遍历（集合就是[1,...,n] ）
    // 2.回溯函数终止条件：什么时候到达叶子节点。path这个数组的大小如果达到k，说明我们找到了一个子集大小为k的组合，在图中path存的就是根节点到叶子节点的路径。
    if (path.size() == k)
    {
      result.push_back(path);
      return; // return是终止当前函数的执行，函数的控制流会立即结束，后续的代码不会被执行。这样就可以完成正确的回溯终止
    }
    // 上面的终止条件一定要在下面的for循环之前，因为如果在for循环之后，就会出现path.size()==k的情况，但是path.size()!=k的情况，这样就会出现错误的结果。
    // 3.单层搜索的过程：回溯法的搜索过程就是一个树型结构的遍历过程，在如下图中，可以看出for循环用来横向遍历，递归的过程是纵向遍历。
    for (int i = startIndex; i <= n; i++)
    {
      path.push_back(i);         // 处理节点
      backtracking(n, k, i + 1); // 递归
      path.pop_back();           // 回溯，撤销处理的节点
    }
  }

public:
  vector<vector<int>> combine(int n, int k)
  {
    result.clear(); // 清空result，防止上次的结果影响本次的结果
    path.clear();   // 清空path，防止上次的结果影响本次的结果
    // 上述可以不写
    backtracking(n, k, 1);
    return result;
  }
};



/*
优化
for(int i=startIndex;i<=n-(k-path.size())+1;i++){
}


*/