////使用栈进行迭代遍历,中序遍历
//刚刚写的前序遍历的代码，不能和中序遍历通用呢，因为前序遍历的顺序是中左右，先访问的元素是中间节点，要处理的元素也是中间节点，所以刚刚才能写出相对简洁的代码，因为要访问的元素和要处理的元素顺序是一致的，都是中间节点。
//在使用迭代法写中序遍历，就需要借用指针的遍历来帮助访问节点，栈则用来处理节点上的元素。
//中序遍历是左中右，先访问的是二叉树顶部的节点，然后一层一层向下访问，直到到达树左面的最底部，再开始处理节点（也就是在把节点的数值放进result数组中）
#include<iostream>
#include<stack>
#include<vector>
using namespace std;
class Solution {
public:
     vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* node = root;
        while(node!=NULL||!st.empty()){
            //其中node!=NULL一个是判断根节点为空的情况，一个是到达最左端的情况，无右节点，无左节点
            //st.empty()必须在node!=NULL后面，先遍历后，再进行处理
            if(node!=NULL){
                st.push(node);
                node=node->left;
            }else{
                node=st.top();
                st.pop();
                result.push_back(node->val);
                node =node->right;
            }
        }
        return result;

     }
};