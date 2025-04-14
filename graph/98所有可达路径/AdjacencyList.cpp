//所有可达路径，邻接表的写法
//注意是邻接表的写法
#include <iostream>
#include <vector>
#include <list>//C++标准模板库（Standard Template Library，简称STL）中的一个头文件std::list 是一个双向链表容器，它支持在容器的任意位置高效地插入和删除元素。由于其内部实现是链表，因此它在插入和删除操作上具有较高的效率，但在随机访问元素时相对较慢。
using namespace std;
vector<vector<int>> result;//收集所有符合条件的路径
vector<int> path;//存储当前路径
//1.确认递归函数和参数返回值
void dfs(const vector<list<int>> &graph,int x,int n){
    //2.终止条件
    if(x==n){
        //找到一条符合要求的路径
        result.push_back(path);
        return;//函数是void类型，所以不需要返回值
        //退出递归
    }
    //3.处理目前搜索节点出发的路径
    //for 循环使用了C++11引入的基于范围的for循环（Range-based for loop），也称为增强型for循环
    for(int i:graph[x]){
        //graph[x]一开始是graph[1],graph[1]是一个list<int>类型的对象，所以里面是int类型，所以可以直接用int i来接收
        path.push_back(i);//遍历到的节点加入到路径中来
        dfs(graph,i,n);//进入下一层递归
        path.pop_back();//回溯，撤销本节点       
    }
}
int main(){
    //邻接表的写法
    int n,m,s,t;
    cin>>n>>m;//n个节点，m条边
    // 节点编号从1到n，所以申请 n+1 这么大的数组,表示邻接表前面的数组
    vector<list<int>> graph(n+1);//邻接表，list<int>表示每个节点的邻接点
    while(m--){
        cin>>s>>t;//输入边的两个端点
        graph[s].push_back(t);//有向边s->t,将t加入到s的邻接表中
    }
    path.push_back(1);//无论什么路径已经是从0节点出发，从节点1开始搜索，这个不参与回溯
    dfs(graph,1,n);//从节点1开始遍历
    //输出所有符合条件的路径
    if(result.empty()) cout<<-1<<endl;
    else{
        //两层循环
        for(const vector<int> &pa : result){
            for(int i=0;i<pa.size()-1;i++){
                cout<<pa[i]<<"->";//输出路径
            }
            cout<<pa[pa.size()-1]<<endl;//输出路径的最后一个节点
        }
    }


}
