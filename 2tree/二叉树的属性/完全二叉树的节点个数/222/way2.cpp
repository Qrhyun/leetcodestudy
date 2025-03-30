// 迭代法层序遍历求解二叉树的节点个数
#include <iostream>
#include <queue>
using namespace std;
class Solution
{
public:
  int countNodes(TreeNode *root)
  {
    queue<TreeNode *> que;
    if (root != NULL)
      que.push(root);
    int result = 0;
    while (!que.empty())
    {
      int size = que.size();
      for (int i = 0; i < size; i++)
      {
        TreeNode *node = que.front();
        que.pop();
        result++;
        if (node->left)
          que.push(node->left);
        if (node->right)
          que.push(node->right);
      }
    }
    return result;
  }
};