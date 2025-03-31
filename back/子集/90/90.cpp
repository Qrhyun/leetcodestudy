/*
当集合里面有重复元素，注意去重需要先对集合排序，比如1.2.2
树层去重和树枝去重
     - 树层去重：在树的每一层中，去掉重复元素，避免出现重复的子集。
     - 树枝去重：在树的每一层中，去掉重复元素，避免出现重复的子集。
     - 注意：
         - 树层去重：需要对数组进行排序，然后在递归函数中判断当前元素是否和前一个元素相同，如果相同则跳过。
*/
// 法一：求子集问题加去重
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
private:
  vector<vector<int>> result; // 存放符合条件结果的集合
  vector<int> path;           // 用来存放符合条件结果
  void backtracking(vector<int> &nums, int startIndex, vector<bool> &used)
  {
    // 利用used实现树层去重和树字可以重复使用
    result.push_back(path); // 收集子集，要放在终止添加的上面，否则会漏掉自己,自己是[],自己也是一个子集,  以前的写法是放在下面的，放在下面会漏掉自己.同时可以将这条路上上的每个节点都加进去
    for (int i = startIndex; i < nums.size(); i++)
    { // 终止条件加在了循环里面，所以不用在终止条件里面加了
      // 树层去重,对同一树层的使用过的元素进行跳过,注意是同一树层,不是同一树枝,因为同一树枝的元素可以重复使用，跳过用continue
      if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false)
      {
        continue;// i>0 是因为i=0的时候，i-1会越界,nums[i]==nums[i-1]是因为要对同一树层的使用过的元素进行跳过,used[i-1]==false是要区分同一数层还是同一树枝的元素
      }
      // used[i - 1] == true，说明同一树枝candidates[i - 1]使用过
      // used[i - 1] == false，说明同一树层candidates[i - 1]使用过、
      path.push_back(nums[i]);
      used[i] = true; // 这里标记为true,是为了进入回溯函数，进行纵向遍历，因为当标记为true的时候，不会进入if语句,所以不会跳过重复元素
      backtracking(nums, i + 1, used);
      used[i] = false; // 这里又标记为false,是为了进入回溯函数，进行横向遍历,横向遍历的话，used[i]是false,所以会进入if语句,所以会跳过重复元素
      path.pop_back();
    }
  }

public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums)
  {
    result.clear();
    path.clear();
    vector<bool> used(nums.size(), false); // 一开始都标记为false,自然的满足if语句里面的条件
    sort(nums.begin(), nums.end());        // 去重需要排序
    backtracking(nums, 0, used);
    return result;
  }
};