// 完全二叉树的节点个数
// 递归法中的后序遍历
#include <iostream>
using namespace std;
class Solution
{
private:
  int getNodesNum(TreeNode *cur)
  {
    if (cur == NULL)
      return 0;                             // 确定终止条件
    int leftNum = getNodesNum(cur->left);   // 左
    int rightNum = getNodesNum(cur->right); // 右
    // 中，处理逻辑
    int treeNum = leftNum + rightNum + 1; // 加一是因为要算上当前节点
    return treeNum;
  }

public:
  int countNodes(TreeNode *root)
  {
    return getNodesNum(root);
  }
};





/*
精简
class Solution {
public:
    int countNodes(TreeNode* root){
        if(root==NULL) return 0;
        return countNodes(root->left)+countNodes(root->right)+1;}
};


*/