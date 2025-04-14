//所有可达路径，邻接矩阵法
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<int>> result;//收集所有符合条件的路径
vector<int> path;//存储当前路径
//1.确认递归函数和参数返回值
void dfs (const vector<vector<int>> &graph,int x,int n){
    //2.终止条件
    if(x==n){
        //找到一条符合要求的路径
        result.push_back(path);
        return;//函数是void类型，所以不需要返回值
        //退出递归
    }
    //3.处理目前搜索节点出发的路径
    for(int i=1;i<=n;i++){
        if(graph[x][i]==1){
            path.push_back(i);//遍历到的节点加入到路径中来
            dfs(graph,i,n);//进入下一层递归
            path.pop_back();//回溯，撤销本节点
        }
    }
}

int main(){
    int n,m,s,t;
    cin>>n>>m;//n个节点，m条边
    // 节点编号从1到n，所以申请 n+1 这么大的数组,邻接数组
    vector<vector<int>> graph(n+1,vector<int>(n+1;0));
    //初始化邻接矩阵，默认值为0
    while(m--){
        cin>>s>>t;//输入边的两个端点
        graph[s][t]=1;//有向边s->t
    }
    path.push_back(1);//无论什么路径已经是从0节点出发，从节点1开始搜索，这个不参与回溯
    dfs(graph,1,n);//从节点1开始遍历
    //输出所有符合条件的路径
    if(result.empty()) cout<<-1<<endl;
    else{
        //两层循环
        for(const vector<int> &pa : result){
            //基于范围的for循环（range-based for loop）来遍历一个名为result的容器中的元素.&：表示pa是一个引用，它直接引用result中的每个元素，而不是复制它们。这可以提高效率，尤其是当容器较大时。
           for(int i=0;i<pa.size()-1;i++){
              cout<<pa[i]<<""
           }
           cout<<pa[pa.size()-1]<<endl;
        }
    }
    
}
//根据 C++ 标准（ISO/IEC 14882:2017），如果 main 函数没有显式返回值，程序会自动返回 0