// 求深度可以从上到下去查 所以需要前序遍历（中左右），而高度只能从下到上去查，所以只能后序遍历（左右中）
// 之所以在求二叉树的最大深度时候也用的后序遍历，那是因为代码的逻辑其实是求的根节点的高度，而根节点的高度就是这棵树的最大深度
// 平衡二叉树：一个二叉树每个节点的左右两个子树的高度差的绝对值不超过1。注意是每个节点

// 后序遍历求高度
#include <iostream>
using namespace std;
class Solution
{
public:
  int getHeight(TreeNode *node)
  {
    if (node == NULL)
      return 0;
    int leftHeight = getHeight(node->left);
    if (leftHeight == -1)
      return -1; // 左子树不平衡，直接返回-1，b不用做后面的了
    int rightHeight = getHeight(node->right);
    if (rightHeight == -1)
      return -1; // 右子树不平衡，直接返回-1
    // 中
    int result;
    if (abs(leftHeight - rightHeiht) > 1)
    {
      result = -1;
    }
    else
    {
      result = 1 + max(leftHeight, rightHeight); // 以当前节点为根节点的树的最大高度
    }
  }
};
