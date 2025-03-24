//层序遍历的时候，判断是否遍历到单层的最后面的元素，如果是，就放进result数组中，随后返回result就可以了。
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class Solution {
public:
   vector<int> rightSideView(TreeNode* root) {
     //这里结果只返回一维数组
     queue<TreeNode*> que;
     if(root!=NULL) que.push(root) ;
     vector<int> result;
     while(!que.empty()){
        int size=que.size();
        for(int i =0;i<size;i++){
            TreeNode* node =que.front();
            que.pop();
            if(i==size-1) result.push_back(node->val);//如果是单层的最后面的元素，就放进result数组中
            if(node->left) que.push(node->left);
            if(node->right) que.push(node->right);
        }
     }
     return result;
   }
};