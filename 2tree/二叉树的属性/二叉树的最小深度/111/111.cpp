// 二叉树的最小深度是从根节点到最近叶子节点的最短路径上的节点数量。注意是叶子节点
// 有一个误区：根节点只有一个子节点，那么最小深度不是1，注意是叶子节点

/*
法一：递归法后序遍历
//如果按照最大深度的写法，会发现上述的误区
   - 解决办法（在每一个父节点处）
      - 如果左子树为空，右子树不为空，说明最小深度是1+右子树的深度。
      - 如果右子树为空，左子树不为空，说明最小深度是1+左子树的深度。
#include <iostream>
using namespace std;
class Solution{
public:
    int getDepth(TreeNode* node){
       if(node==NULL) return 0;
       int leftDepth = getDepth(node->left);//左
       int rightDepth = getDepth(node->right);//右
       //中,所有的逻辑都在中间汇总处理的时候
       //第一种情况：左子树为空，右子树不为空，说明最小深度是1+右子树的深度。
       if(node->left==NULL&&node->right!=NULL) return 1+rightDepth;
       //第二种情况：右子树为空，左子树不为空，说明最小深度是1+左子树的深度。
       if(node->left!=NULL&&node->right==NULL) return 1+leftDepth;
       //第三种情况：左右子树都不为空，说明最小深度是1+左右子树的深度的最小值。
       int result = 1+min(leftDepth,rightDepth);
       return result;

    }
    int minDepth(TreeNode* root){
        return getDepth(root);
    }
};

法二：精简法
#include <iostream>
using namespace std;
class Solution{
public:
    int minDepth(TreeNode* root){
       if(root==NULL) return 0;
       if(root->left==NULL&&root->right!=NULL) return 1+minDepth(root->right);
       if(root->left!=NULL&&root->right==NULL) return 1+minDepth(root->left);
       return 1+min(minDepth(root->left),minDepth(root->right));
    }
};

法三：递归法前序遍历
#include <iostream>
using namespace std;
class Solution {
private:
    int result;
    void getdepth(TreeNode* node, int depth) {
        // 函数递归终止条件
        if (node == nullptr) {
            return;
        }
        // 中，处理逻辑：判断是不是叶子结点
        if (node -> left == nullptr && node->right == nullptr) {
            result = min(result, depth);
        }
        if (node->left) { // 左
            getdepth(node->left, depth + 1);
        }
        if (node->right) { // 右
            getdepth(node->right, depth + 1);
        }
        return ;
    }

public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        result = INT_MAX;
        getdepth(root, 1);
        return result;
    }
};
法四：迭代法
#include <iostream>
#include <queue>
using namespace std;
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        int depth = 0;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            depth++; // 记录最小深度，这个是和层数绑定的
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
                //与最大深度的区别在于下面两句：当左右孩子都为空的时候，说明是最低点的一层了，退出
                if (!node->left && !node->right) {
                 // 当左右孩子都为空的时候，说明是最低点的一层了，退出

                    return depth;
                    //只有当左右孩子都为空的时候，才说明遍历到最低点了。如果其中一个孩子不为空则不是最低点
                 //这个保证了两点：
                 //- 且的关系避免了上面的误区
                 //- 然后也保证了一遇到满足的情况就结束的情况，return depth 会直接退出整个函数，而不仅仅是 while 循环
                    }
            }
        }
        return depth;//到最后一直同时长度并行，那么就返回其中一个

    }
};


return
- 终止当前函数的执行
 当 return 被执行时，函数的控制流会立即结束，后续的代码不会被执行。
 如果函数有返回值，return 会将指定的值返回给调用该函数的地方。
- 清理函数栈帧(编译原理)
 在函数调用时，系统会为该函数分配一个栈帧，用于存储局部变量、参数和返回地址。
 执行 return 时，编译器会生成指令来清理当前函数的栈帧，并恢复调用函数的上下文。
- 跳转到返回地址
 每个函数调用时，调用者的返回地址会被存储在栈中。
 return 的底层实现会将控制流跳转到存储的返回地址，从而回到调用函数的地方。
*/
#include <iostream>
#include <queue>
using namespace std;
class Solution
{
public:
  int minDepth(TreeNode *root)
  {
    if (root == NULL)
      return 0;
    int depth = 0;
    queue<TreeNode *> que;
    que.push(root);
    while (!que.empty())
    {
      int size = que.size();
      depth++; // 记录最小深度，这个是和层数绑定的
      for (int i = 0; i < size; i++)
      {
        TreeNode *node = que.front();
        que.pop();
        if (node->left)
          que.push(node->left);
        if (node->right)
          que.push(node->right);
        // 与最大深度的区别在于下面两句：当左右孩子都为空的时候，说明是最低点的一层了，退出
        if (!node->left && !node->right)
        {
          // 当左右孩子都为空的时候，说明是最低点的一层了，退出
          while (!que.empty())
            que.pop(); // 清空队列
          return depth;
          // 只有当左右孩子都为空的时候，才说明遍历到最低点了。如果其中一个孩子不为空则不是最低点
          // 这个保证了两点：
          //- 且的关系避免了上面的误区
          //- 然后也保证了一遇到满足的情况就结束的情况，return depth 会直接退出整个函数，而不仅仅是 while 循环
        }
      }
    }
    return depth; // 到最后一直同时长度并行，那么就返回其中一个
  }
};