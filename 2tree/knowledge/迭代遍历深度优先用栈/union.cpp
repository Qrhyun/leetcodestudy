//统一迭代遍历,用栈
//使用栈的话，无法同时解决访问节点（遍历节点）和处理节点（将元素放进结果集）不一致的情况。
//将访问的节点放入栈中，把要处理的节点也放入栈中但是要做标记
/*
法一：
   - 处理节点放入栈之后，紧接着放入一个空指针作为标记
法二：
   - 加一个boolean跟随每一个节点
      - false 表示需要为该节点和它的左右儿子安排在栈中的位次
      - true 表示该节点的位次已经安排好了，可以进行处理（放入结果集result）


*/


/*
中序遍历
法一：空指针法
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    if(root=NULL) st.push(root);
    while(!st.empty()){
       TreeNode* node=st.top();
       if(node!=NULL){
        st.pop();// 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
        if(node->right) st.push(node->right);//先添加右节点
        st.push(node);//添加中节点
        st.push(NULL);//中节点访问过，但是还没有处理，加入空节点做为标记。
        }else{
        //只有遇到空节点的时候，才将下一个节点放进结果集
        st.pop();//将空节点弹出
        node=st.top();//重新取出栈中元素,这里pop在前面，所以要重新取一次
        st.pop();
        result.push_back(node->val);//加入到结果集
        }
       }
     return result;
    }
};
*/


/*
法二：bool跟随法
## stack<pair<TreeNode*,bool>> st,表示一个栈（stack），其中每个元素是一个 pair（键值对）,这个 pair 包含两个部分：
   - 一个是 TreeNode 类型的指针（TreeNode*），表示树中的节点。
   - 另一个是 bool 类型的值，表示节点是否被访问过。
      - false 表示节点尚未被访问过。
      - true 表示节点已经被访问过。
## st.push(make_pair(root,false));
   - 表示将一个 pair 类型的元素（make_pair(root, false)）压入栈 st 中。
   - make_pair(root, false) 创建一个新的 pair，其中第一个元素是 root（树的根节点），第二个元素是 false（表示节点尚未被访问过）。
   - 来自于 <utility> 头文件，用于创建键值对。
       - std::pair是一个模板类，用于存储两个不同类型的值。
       - std::make_pair是一个函数模板，用于创建并返回一个std::pair对象。是一个辅助函数，用于简化创建std::pair对象的过程   
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<pair<TreeNode*,bool>> st;
    if(root!=NULL) st.push(make_pair(root,false));
    while(!st.empty()){
       auto node=st.top().first;
       auto flag=st.top().second;
       st.pop(); //防止重复操作
       if(flag){
       //如果flag为true，说明已经访问过，在加入到结果集
       result.push_back(node->val);
       continue;
       }
       //flag为false，说明还没有访问过,需要将右中左节点添加到栈中
       if(node->right) st.push(make_pair(node->right,false));
       st.push(make_pair(node,true));
       if(node->left) st.push(make_pair(node->left,false));
    }
    return result;
    }   
};

*/



/*
前序遍历空指针
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != NULL) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != NULL) {
                st.pop();
                if (node->right) st.push(node->right);  // 右
                if (node->left) st.push(node->left);    // 左
                st.push(node);                          // 中
                st.push(NULL);
            } else {
                st.pop();
                node = st.top();
                st.pop();
                result.push_back(node->val);
            }
        }
        return result;
    }
};


*/


/*
后续遍历空指针
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != NULL) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != NULL) {
                st.pop();
                st.push(node);                          // 中
                st.push(NULL);

                if (node->right) st.push(node->right);  // 右
                if (node->left) st.push(node->left);    // 左

            } else {
                st.pop();
                node = st.top();
                st.pop();
                result.push_back(node->val);
            }
        }
        return result;
    }
};

*/


/*
后序遍历bool跟随法
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<pair<TreeNode*, bool>> st;
        if (root != nullptr)
            st.push(make_pair(root, false)); // 多加一个参数，false 为默认值，含义见下文

        while (!st.empty()) {
            auto node = st.top().first;
            auto visited = st.top().second; //多加一个 visited 参数，使“迭代统一写法”成为一件简单的事
            st.pop();

            if (visited) { // visited 为 True，表示该节点和两个儿子位次之前已经安排过了，现在可以收割节点了
                result.push_back(node->val);
                continue;
            }

            // visited 当前为 false, 表示初次访问本节点，此次访问的目的是“把自己和两个儿子在栈中安排好位次”。
            // 后序遍历是'左右中'，节点自己最先入栈，最后出栈。
            // 同时，设置 visited 为 true，表示下次再访问本节点时，允许收割。
            st.push(make_pair(node, true));

            if (node->right)
                st.push(make_pair(node->right, false)); // 右儿子位置居中

            if (node->left)
                st.push(make_pair(node->left, false)); // 左儿子最后入栈，最先出栈
        }
        
        return result;
    }
};



*/