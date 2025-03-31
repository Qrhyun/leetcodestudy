// 如果把 子集问题、组合问题、分割问题都抽象为一棵树的话，那么组合问题和分割问题都是收集树的叶子节点，而子集问题是找树的所有节点！
// 既然是无序，取过的元素不会重复取，写回溯算法的时候，for就要从startIndex开始，而不是从0开始！
// 求排列问题的时候，就要从0开始，因为集合是有序的，{1, 2} 和{2, 1}是两个集合

#include <iostream>
#include <vector>
using namespace std;
class Solution
{
private:
  vector<vector<int>> result; // 存放符合条件结果的集合
  vector<int> path;           // 用来存放符合条件结果
  void backtracking(vector<int> &nums, int startIndex)
  {
    result.push_back(path); // 收集子集，要放在终止添加的上面，否则会漏掉自己,自己是[],自己也是一个子集,  以前的写法是放在下面的，放在下面会漏掉自己.同时可以将这条路上上的每个节点都加进去
    // 终止条件
    if (startIndex >= nums.size())
      return;
    // 单层递归逻辑
    for (int i = startIndex; i < nums.size(); i++)
    {
      path.push_back(nums[i]);
      backtracking(nums, i + 1);
      path.pop_back(); // 回溯，撤销处理的节点
    }
  }

public:
  vector<vector<int>> subsets(vector<int> &nums)
  {
    result.clear();        // 可以不写，因为result是全局变量，每次调用都会清空
    path.clear();          // 可以不写，因为path是全局变量，每次调用都会清空
    backtracking(nums, 0); // 从0开始遍历.从下标0开始遍历
    return result;
  }
};
