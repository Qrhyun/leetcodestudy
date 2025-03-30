// 二叉树的最大深度和高度
//   - 二叉树的最大深度：根节点到最远叶子节点的最长路径上的节点数
//   - 二叉树的高度：根节点到最远叶子节点的最长路径上的节点数
// 二叉树节点的深度（注意二叉树的最大深度和节点的深度是不同的）
//   - 二叉树节点的深度：根节点到该节点的最长简单路径边的条数或节点数（取决于深度从0开始还是从1开始）
//   - 二叉树节点的高度：该节点到叶子节点的最长简单路径边的条数或节点数（取决于高度从0开始还是从1开始）
// 深度和高度的区别
//   - 节点的深度：指从根节点到该节点的最长简单路径边的条数或节点数（取决于深度从0开始还是从1开始）
//   - 节点的高度：指从该节点到叶子节点的最长简单路径边的条数或节点数（取决于高度从0开始还是从1开始）
// 因此可以看出
//   - 二叉树的最大深度就是根节点的高度
//   - 二叉树的的最大高度就是根节点的深度
//   - 二叉树的高度和深度是相同的，都是从根节点到最远叶子节点的最长路径上的节点数（取决于高度从0开始还是从1开始）

/*
法一：递归法中的后序遍历
//通过后序求的根节点高度来求的二叉树最大深度。
//这里的递归后序遍历和对称二叉树的递归后续遍历很像，都是先定义一个函数里面递归包含递归，然后在主函数里面调用这个函数，主函数传入的是根节点
#include <iostream>
using namespace std;
class Solution{
public:
   int getDepth(TreeNode* node){
   //首先排除空根节点的情况
   if(node==NULL) return 0;
   //后序遍历，求根节点的高度
   int leftdepth = getDepth(node->left);//左
   int rightdepth = getDepth(node->right);//右
   int depth = 1+ max(leftdepth,rightdepth);//中
   //这里的1是因为根节点的高度是1
   return depth;
   }
   int maxDepth(TreeNode* root){
     return getDepth(root);
   }
};


法二：递归法的精简版本
//把上述代码中的getDepth函数和maxDepth函数合并
#include <iostream>
using namespace std;
class Solution{
public:
  int maxDepth(TreeNode* root){
    if(root==NULL) return 0;
    return 1+max(maxDepth(root->left),maxDepth(root->right));
  }
};

//上面的后序遍历隐藏了太多回溯
法三：递归法中的前序遍历充分表现出求深度回溯的过程
//通过前序求的根节点高度来求的二叉树最大深度。
#include <iostream>
using namespace std;
class Solution{
public:
   int result;//定义一个全局变量，用来存放最大深度，必须放在最上面，下面要用
   void getDepth(TreeNode* node,int depth){
    //首先排除空根节点的情况
    result =depth>result?depth:result;//中
    if(node->left==NULL&&node->right==NULL) return;//这是终止条件，因为叶子节点的左右孩子都是空节点，所以这里要终止,因此这里是且的关系
    if(node->left){//左
    depth++;
    getDepth(node->left,depth);
    depth--;//回溯.在此一轮迭代中depth我要保证不变
    }
    if(node->right){//右
    depth++;
    getDepth(node->right,depth);
    depth--;//回溯.在此一轮迭代中depth我要保证不变
    }
    return;
   }
    int maxDepth(TreeNode* root){
     result=0;//初始化最大深度为0
     if(root==NULL) return result;
     getDepth(root,1);//传入根节点和深度1
     return result;
    }
};

法泗：精简
class Solution {
public:
    int result;
    void getdepth(TreeNode* node, int depth) {
        result = depth > result ? depth : result; // 中
        if (node->left == NULL && node->right == NULL) return ;
        if (node->left) { // 左
            getdepth(node->left, depth + 1);
        }
        if (node->right) { // 右
            getdepth(node->right, depth + 1);
        }
        return ;
    }
    int maxDepth(TreeNode* root) {
        result = 0;
        if (root == 0) return result;
        getdepth(root, 1);
        return result;
    }
};
*/

/*
法五：迭代法
//使用层序遍历是最为合适的，因为最大的深度就是二叉树的层数，和层序遍历的方式极其吻合。
#include <iostream>
#include <queue>
using namespace std;
class Solution {
public:
    int maxDepth(TreeNode* root) {
     if(root==NULL) return 0;
     int depth = 0;
     queue<TreeNode*> que;
     que.push(root);//先把根节点压入队列
     while(!que.empty()){
      int size = que.size();//因为要记录每一层的节点个数，为的是所有的点都执行下述for循环
      depth++;//每一层的节点个数就是二叉树的深度,先把根节点的深度加1
      for(int i=0;i<size;i++){
       TreeNode* node = que.front();//用一个临时的树节点来容纳队列的头节点
       que.pop();
       if(node->left) que.push(node->left);//如果左节点不为空，就把左节点压入队列
       if(node->right) que.push(node->right);//如果右节点不为空，就把右节点压入队列
       //队列是先进先出，所以先把左节点压入队列，再把右节点压入队列，这样才能保证顺序 
      } 
     }
     return depth;
    }
};

*/