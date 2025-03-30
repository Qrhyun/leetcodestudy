// 在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层，则该层包含 1~ 2^(h-1)  个节点。
// 完全二叉树只有两种情况，情况一：就是满二叉树，情况二：最后一层叶子节点没有满。
//  - 情况1：满二叉树，节点个数为 2^h - 1
//  - 情况2：最后一层叶子节点没有满，节点个数为 2^(h-1) - 1 + 1~2^(h-1)
//  - 分别递归左孩子，和右孩子，递归到某一深度一定会有左孩子或者右孩子为满二叉树，然后依然可以按照情况1来计算。
//  - 判断其子树是不是满二叉树，如果是则利用公式计算这个子树（满二叉树）的节点数量，如果不是则继续递归
//  -在完全二叉树中，如果递归向左遍历的深度等于递归向右遍历的深度，那说明就是满二叉树
#include <iostream>
using namespace std;
class Solution
{
public:
  int countNodes(TreeNode *root)
  {
    if (root == NULL)
      return 0;
    TreeNode *left = root->left;
    TreeNode *right = root->right;
    int leftDepth = 0, rightDepth = 0; // 这里初始为0是有目的的，为了下面求指数方便,即为了后面用公式方便
    while (left)
    {//while循环判断
      left = left->left;
      leftDepth++;
    }
    while (right)
    {
      right = right->right;
      rightDepth++;
    }
    if (leftDepth == rightDepth)
    {
      return (2 << leftDepth) - 1; // 2<<leftDepth = 2^(leftDepth+1) = 2^(h+1) = 2^h * 2^1 = 2^h * 2 = 2^(h+1) - 1
    }
    return countNodes(root->left) + countNodes(root->right) + 1;
  }
};