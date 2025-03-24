// 翻转二叉树，实际上就是把每一个节点的左右孩子交换一下就可以了
// 建议前序和后续遍历的时候进行翻转，因为这样可以保证根节点的左右孩子已经翻转完毕了，而中序遍历会把根节点的左右孩子翻转两次

// 递归三步法
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  // 1. 确定递归函数的参数和返回值
  TreeNode *invertTree(TreeNode *root)
  {
    if (root == NULL)
      return root;                 // 如果根节点为空，就返回根节点  2.递归终止条件
    swap(root->left, root->right); // 对于中间节点，交换左右孩子  3. 单层递归逻辑
    invertTree(root->left);        // 左  4. 递归
    invertTree(root->right);       // 右
    return root;                   // 返回根节点,这句一定要在最后一句，否则会返回空
  }
};

// 迭代法深度优先
// 使用栈进行迭代遍历,前序遍历
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
class Solution
{
public:
  TreeNode *invertTree(TreeNode *root)
  {
    stack<TreeNode *> st;
    if (root == NULL)
      return root; // 这里是要求结果的树，不像前面要求数组，所以就算是空树也要返回
    st.push(root);
    while (!st.empty())
    {
      TreeNode *node = st.top();
      st.pop();
      swap(node->left, node->right);
      // 这句一定要在下面两句前面，先完成一层的交换，再进行下一层的压栈
      if (node->right)
        st.push(node->right);
      if (node->left)
        st.push(node->left);
      // 这里是前序遍历，所以先压入右节点，再压入左节点
    }
    return root;
  }
};

// 迭代法广度优先
// 使用队列进行迭代遍历,层序遍历
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class Solution
{
public:
  TreeNode *invokerTree(TreeNode *root)
  {
    queue<TreeNode *> q;
    if (root == NULL)
      return root;
    q.push(root);
    while (!q.empty())
    {
      int size = q.size();
      for (int i = 0; i < size; i++)
      {
        TreeNode *node = q.front();
        q.pop();
        swap(node->left, node->right);
        if (node->left)
          q.push(node->left);
        if (node->right)
          q.push(node->right);
        // 这里是层序遍历，所以先压入左节点，再压入右节点
      }
    }
    return root;
  }
};