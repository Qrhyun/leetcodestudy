#include <iostream>
#include <vector>
#include <unordered_set> //unordered_set 是 C++ 标准模板库（STL）中的一个容器类，定义在 <unordered_set> 头文件中。它是一个哈希表实现的集合，提供快速的插入、删除和查找操作，时间复杂度平均为 O(1)。
                         // - insert 是 unordered_set 的成员函数，用于向集合中插入一个元素。如果元素已经存在，则插入操作不会改变集合。
                         // - find 是 unordered_set 的成员函数，用于查找集合中是否存在某个元素。
                              // - 如果 value 存在于集合中，find 返回一个指向该元素的迭代器。
                              // - 如果 value 不存在于集合中，find 返回一个指向集合末尾的迭代器。（end()）
                         // - 迭代器（Iterator）是 C++ 标准模板库（STL）中提供的一种工具，用于遍历容器（如 vector、unordered_set 等）中的元素。它可以看作是一个指针，但功能更强大，能够以统一的方式访问不同类型的容器。
                              // - begin()：返回指向容器第一个元素的迭代器
                              // - end()：返回指向容器末尾之后的迭代器（不指向任何元素）
#include <algorithm>
using namespace std;
class Solution
{
private:
  vector<vector<int>> result; // 存放符合条件结果的集合
  vector<int> path;           // 用来存放符合条件结果
  void backtracking(vector<int> &nums, int startIndex)
  {
    result.push_back(path); // 收集子集，要放在终止添加的上面，否则会漏掉自己,自己是[],自己也是一个子集,  以前的写法是放在下面的，放在下面会漏掉自己.同时可以将这条路上上的每个节点都加进去
    unordered_set<int> uset;
    for (int i = startIndex; i < nums.size(); i++)
    {
      if (uset.find(nums[i]) != uset.end())
      {
        continue; // 如果当前元素已经存在于集合中，已经可以找到，则跳过该元素，避免重复添加
      }
      uset.insert(nums[i]);
      path.push_back(nums[i]);
      backtracking(nums, i + 1); // 递归
      path.pop_back();
    }
  }

public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums)
  {
    result.clear();                 // 可以不写
    path.clear();                   // 可以不写
    sort(nums.begin(), nums.end()); // 去重需要排序
    backtracking(nums, 0);
    return result;
  }
};