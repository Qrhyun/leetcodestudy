//递归法层序遍历
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    void order(TreeNode* cur,vector<vector<int>>& result,int depth){
        if(cur==NULL) return;
        if(result.size()==depth) result.push_back(vector<int>());//如果result的大小等于depth，就把一个一维数组放进result
    }
};