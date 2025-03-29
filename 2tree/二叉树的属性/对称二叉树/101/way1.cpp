//对称二叉树
//正是因为要遍历两棵树而且要比较内侧和外侧节点，所以准确的来说是一个树的遍历顺序是左右中，一个树的遍历顺序是右左中。
/*
//法一：递归法
   // - 使用后序遍历
#include <iostream>
using namespace std;
class Solution{
public:
    bool compare(TreeNode* left,TreeNode* right){
        //这里要传入两个节点，一个是左子树的根节点，一个是右子树的根节点
        //首先排除空节点的情况
        if(left==NULL&&right!=NULL) return false;
        else if(left!=NULL&&right==NULL) return false;
        else if(left==NULL&&right==NULL) return true;
         //此时就是：左右节点都不为空，且数值相同的情况
         //此时才做递归，做下一层的判断
         bool outside =compare(left->left,right->right); // 左子树：左、 右子树：右
         bool inside = compare(left->right,right->left); // 左子树：右、 右子树：左
         return outside&&inside;// 左子树：中、 右子树：中 （逻辑处理）
    }
    bool isSymmetric(TreeNode* root){
        if(root == NULL) return true;
        return compare(root->left,root->right);
    }
    //这个函数必须在上面那个函数的下面，因为它用到了上面那个函数
};
*/

/*

//法二：迭代法
  // - 使用队列，注意这不是层序遍历，而是一种特殊的层序遍历
#include <iostream>
#include <queue>
using namespace std;
class Solution{
public:
    bool compare(TreeNode* root){
    //首先排除空根节点的情况
    if(root==NULL) return true;(
    //创建一个队列，用来存放树的节点
    queue<TreeNode*> que;
    que.push(root->left);
    que.push(root->right);
    while(!que.empty()){
        //取出队列中的两个节点
        TreeNode* left =que.front(); que.pop();
        TreeNode* right =que.front(); que.pop();
        //排除空节点的情况, 这里和递归法一样
        if(!left&&!right) continue;
        if( (!left&&right )||(left&&!right)||(left->val!=right->val)))
        return false;
        //此时就是：左右节点都不为空，且数值相同的情况
        queue.push(left->left);
        queue.push(right->right);
        queue.push(left->right);
        queue.push(right->left);
        //按照判断逻辑压入队列，执行下一层循环
        }
    
    
    //在执行完所有的循环判断之后，如果没有返回false，那么就返回true
    return true;
    
    }
};
   


   // - 使用栈
#include <iostream>
#include <stack>
using namespace std;
class Solution{
public:
    bool compare(TreeNode* root){
    //首先排除空根节点的情况
    if(root==NULL) return true;
    //创建一个栈，用来存放树的节点
    stack<TreeNode*> sta;
    sta.push(root->left);
    sta.push(root->right);
    while(!sta.empty()){
       //去除栈中的两个节点
       TreeNode*  right = sta.top(); sta.pop();
         TreeNode*  left = sta.top(); sta.pop();
        //排除空节点的情况, 这里和递归法一样
        if(!left&&!right) continue;
       if(( (!left&&right )||(left&&!right)||(left->val!=right->val))) return false;
        //此时就是：左右节点都不为空，且数值相同的情况
        sta.push(left->left);
        sta.push(right->right);
        sta.push(left->right);
        sta.push(right->left);
        //按照判断逻辑压入栈，执行下一层循环
        }
    return true;
}
};




*/