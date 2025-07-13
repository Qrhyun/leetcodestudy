//
// Created by 15089 on 25-7-5.
// 输入前序遍历与中序遍历，重建处该二叉树

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 函数用于根据前序和中序遍历结果重建二叉树
TreeNode* reConstructBinaryTree(vector<int>& pre, vector<int>& vin) {
    // 如果前序或中序遍历为空，或者中序遍历只有一个元素，返回NULL
    if (pre.size() == 0 || vin.size() == 0) {
        return NULL;
    }

    // 创建根节点，其值为前序遍历的第一个元素
    TreeNode* treeNode = new TreeNode(pre[0]);

    // 在中序遍历中找到根节点的位置
    int mid = distance(begin(vin), find(begin(vin), end(vin), pre[0]));

    // 根据根节点的位置，分割前序和中序遍历数组
    vector<int> left_pre(pre.begin() + 1, pre.begin() + mid + 1);
    vector<int> right_pre(pre.begin() + mid + 1, pre.end());
    vector<int> left_in(vin.begin(), vin.begin() + mid);
    vector<int> right_in(vin.begin() + mid + 1, vin.end());

    // 递归构建左子树和右子树
    treeNode->left = reConstructBinaryTree(left_pre, left_in);
    treeNode->right = reConstructBinaryTree(right_pre, right_in);

    // 返回构建好的二叉树的根节点
    return treeNode;
}