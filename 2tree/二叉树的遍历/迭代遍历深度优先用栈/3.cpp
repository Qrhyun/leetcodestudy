//使用栈进行迭代遍历,后序遍历
//先序遍历是中左右，后序遍历是左右中，那么我们只需要调整一下先序遍历的代码顺序，就变成中右左的遍历顺序，然后在反转result数组，输出的结果顺序就是左右中了
#include<iostream>
#include<stack>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
       vector<int> result;
       stack<TreeNode*> st;
       TreeNode* node = root;
       if(node==NULL) return result;
       //这里忘记压入根节点了
       st.push(node);
       while(!st.empty()){
           node=st.top();
           st.pop();
           result.push_back(node->val);
           if(node->left) st.push(node->left);
           if(node->right) st.push(node->right);
       }
       reverse(result.begin(),result.end()); 
       return result; 
    }
};