//使用栈进行迭代遍历,前序遍历
#include<iostream>
#include<stack>
#include<vector>
using namespace std;
class Solution {
    public:
        vector<int> preorderTraversal(TreeNode* root) {
            stack<TreeNode*> st;//建立一个树节点的栈，树节点用结构体构成
            vector<int> result;//建立一个容器容纳结果的数组
            if (root == NULL) return result;//验证根节点，保证代码的健壮性
            st.push(root);//压入根节点
            while (!st.empty()) {
            //用st.empty()时候，最好用while，不要用for
                TreeNode* node = st.top();                       // 中
                st.pop();//因为是在弹出栈后才进行遍历，因此应该让一个临时的树节点容纳top.并执行pop
                result.push_back(node->val);
                if (node->right) st.push(node->right);  //判断语句里面直接node->right         // 右（空节点不入栈）
                if (node->left) st.push(node->left);             // 左（空节点不入栈）
            }
            return result;
        }
    };