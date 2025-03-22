//层序遍历二叉树，用队列
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
    //因为结果是一个二维数组，所以需要用一个二维数组来容纳结果
        queue<TreeNode*> que;
        if(root!=NULL) que.push(root);//先把根节点压入队列
        vector<vector<int>> result;//建立一个二维数组来容纳结果
        while(!queue.empty()){
            int size = que.size();//因为要记录每一层的节点个数，为的是所有的点都执行下述for循环
            vector<int> vec;//建立一个一维数组来容纳每一层的节点。这里每一个while循环就是一层
            for(int i=0;i<size;i++){
            // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的 
                TreeNode* node = que.front();//用一个临时的树节点来容纳队列的头节点
                que.pop();
                vec.push_back(node->val);//把头节点的值放进一维数组
                if(node->left) que.push(node->left);//如果左节点不为空，就把左节点压入队列
                if(node->right) que.push(node->right);//如果右节点不为空，就把右节点压入队列
                //队列是先进先出，所以先把左节点压入队列，再把右节点压入队列，这样才能保证顺序
            }
            result.push_back(vec);//把一维数组放进二维数组
        }
        return result;
    }
};
