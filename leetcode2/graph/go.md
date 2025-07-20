## 理论
### 深度优先搜索分析步骤
- 确认递归函数，参数:dfs函数一定要存一个图，用来遍历的，需要存一个目前我们遍历的节点，定义为x。还需要存一个n，表示终点，我们遍历的时候，用来判断当 x==n 时候 标明找到了终点
- 确认终止条件：什么时候我们就找到一条路径了？当目前遍历的节点为最后一个节点 n 的时候 就找到了一条从出发点到终止点的路径。
- 处理目前搜索节点出发的路径（递归回溯操作）：接下来是走当前遍历节点x的下一个节点。并且递归调用dfs和回溯
- 输出结果：结果都存在了 result数组里（二维数组，每一行是一个结果），最后将其打印出来
### 广度优先搜索分析
- [b站](https://www.bilibili.com/video/BV1M19iY4EL9/?vd_source=b3fd84988e8e921a37b4fa1da8d481db)
`邻接矩阵写法`
```cpp
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 表示四个方向
// grid 是地图，也就是一个二维数组
// visited标记访问过的节点，不要重复访问
// x,y 表示开始搜索节点的下标
void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
    queue<pair<int, int>> que; // 定义队列,队列里面放着元素的坐标

    que.push({x, y}); // 起始节点加入队列
    visited[x][y] = true; // 只要加入队列，立刻标记为访问过的节点

    // 开始遍历队列里的元素
    while(!que.empty()) { 
        // 从队列取元素
        pair<int ,int> cur = que.front(); que.pop(); 

        // 取出当前节点的坐标
        int curx = cur.first;
        int cury = cur.second; 

        // 开始向当前节点的四个方向左右上下去遍历
        for (int i = 0; i < 4; i++) { 
            // 获取周边四个方向的坐标
            int nextx = curx + dir[i][0];
            int nexty = cury + dir[i][1]; 

            // 坐标越界了，直接跳过
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  

            // 如果节点没被访问过
            if (!visited[nextx][nexty]) { 
                que.push({nextx, nexty});  // 队列添加该节点为下一轮要遍历的节点
                visited[nextx][nexty] = true; // 只要加入队列立刻标记，避免重复访问
            }
        }
    }
}
```
### 图的存储
`邻接矩阵使用**二维数组**来表示图结构`
- 邻接矩阵是从**节点**的角度来表示图，有多少节点就申请多大的二维数组
- 本题我们会有n 个节点，因为节点标号是从1开始的，为了节点标号和下标对齐，我们申请 `n + 1 * n + 1` 这么大的二维数组。
```cpp
vector<vector<int>> graph(n+1, vector<int>(n+1, 0));
//输入m个边，构造方式如下
while(m--) {
  cin>>s>>t;
  graph[s][t] = 1;
}
```
`邻接表使用**数组 + 链表**的方式来表示`
- 邻接表是从**边**的数量来表示图，有多少边 才会申请对应大小的链表。
- 这里表达的图是：
> 节点1 指向 节点3 和 节点5
> 节点2 指向 节点4、节点3、节点5
> 节点3 指向 节点4
> 节点4指向节点1
```cpp
// 节点编号从1到n，所以申请 n+1 这么大的数组
vector<list<int>> graph(n+1);//元素为链表
//输入m个边，构造方式如下：
while(m--) {
  cin>>s>>t;
  graph[s].push_back(t);
}
```
## 98.所有可达路径
### 深度优先搜索代码
`邻接j矩阵写法`
```cpp
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int> result;
vector<int> path;

void dfs(const vector<vector<int>> &graph, int x, int n) {
  //当前遍历的节点x到达节点n
  if(x == n) {
    //找到一个符合条件的路径
    result.push_back(path);
    return;
  }
  for(int i = 1; i <= n; i++) {
    //遍历节点x连接的所有相连的节点
    if(graph[x][i] == i) {
      path.push_back(i);// 遍历到的节点加入到路径中来
      dfs(graph, i, n);// 进入下一层递归
      path.pop_back();// 回溯，撤销路径
    }
  }
}

int main() {
  int n, m, s, t;
  cin >> n >> m;

  // 节点编号从1到n,所以申请 n+1 这么大的数组
  vector<vector<int>> graph(n+1, vector<int>(n+1, 0));

  while(m--) {
    cin >> s >> t;
    //使用邻接矩阵表示无向图
    graph[s][t] = 1;
  }

  path.push_back(1); // 无论什么路径已经是从0节点出发
  dfs(graph, 1, n); //开始遍历

  //输出结果
  if(result.size() == 0) cout << -1 << endl;//如果没找到路径，那么返回-1
  for(const vector<int> &pa : result) {
    for(int i = 0; i < pa.size(); i++) {
      cout << pa[i] <<" ";
    }
    cout << pa[pa.size()-1] << endl;
  }

}
```
`邻接表写法`
```cpp
#include <iostream>
#include <vector>
#include <list>
using namesapce std;

vector<vector<int>> result;
vector<int> path;

void dfs(const vector<list<int>> &graph, int x, int n) {
  if(x == n) {
    result.push_back(path);
    return;
  }

  for(int i : graph[x]) {// 找到 x指向的节点链表中的一个节点i
    path.push_back(i); // 遍历到的节点加入到路径来
    dfs(graph, i, n); //进入下一层递归
    path.pop_back(); // 回溯，撤销本节点
  }
}

int main () {
  int n, m, s, t;
    cin >> n >> m;

    // 节点编号从1到n，所以申请 n+1 这么大的数组
    vector<list<int>> graph(n + 1); // 邻接表
    while (m--) {
        cin >> s >> t;
        // 使用邻接表 ，表示 s -> t 是相连的
        graph[s].push_back(t);

    }

    path.push_back(1); // 无论什么路径已经是从0节点出发
    dfs(graph, 1, n); // 开始遍历

    // 输出结果
    if (result.size() == 0) cout << -1 << endl;
    for (const vector<int> &pa : result) {
        for (int i = 0; i < pa.size() - 1; i++) {
            cout << pa[i] << " ";
        }
        cout << pa[pa.size() - 1]  << endl;
    }
}
```


## 99. 岛屿数量
- 本题思路，是用遇到一个没有遍历过的节点陆地，计数器就加一，然后把该节点陆地所能遍历到的陆地都标记上。在遇到标记过的陆地节点和海洋节点的时候直接跳过。 这样计数器就是最终岛屿的数量。那么如何把节点陆地所能遍历到的陆地都标记上呢，就可以使用 DFS，BFS或者并查集。
### `DFS`
```cpp
#include <iostream>
#include <vector>
using namespace std;

int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};// 方向数组，用来表示上、下、左、右四个方向

// 深度优先搜索解决将相邻的陆地都标记为都访问过 ，vector<vector<bool>> &cisited标记是否访问过
void dfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    for (int i = 0; i < 4; i++) {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
        if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) { // 没有访问过的 同时 是陆地的

            visited[nextx][nexty] = true;
            dfs(grid, visited, nextx, nexty);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] == 1) {
                visited[i][j] = true;
                result++; // 遇到没访问过的陆地，+1
                dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
            }
        }
    }

    cout << result << endl;
}
```
```cpp
// 版本二
#include <iostream>
#include <vector>
using namespace std;
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
void dfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    if (visited[x][y] || grid[x][y] == 0) return; // 终止条件：访问过的节点 或者 遇到海水
    visited[x][y] = true; // 标记访问过
    for (int i = 0; i < 4; i++) {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
        dfs(grid, visited, nextx, nexty);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] == 1) {
                result++; // 遇到没访问过的陆地，+1
                dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
            }
        }
    }
    cout << result << endl;
}
```
### `BFS`
```CPP
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
    queue<pair<int, int>> que;
    que.push({x, y});
    visited[x][y] = true; // 只要加入队列，立刻标记
    while(!que.empty()) {
        pair<int ,int> cur = que.front(); que.pop();
        int curx = cur.first;
        int cury = cur.second;
        for (int i = 0; i < 4; i++) {
            int nextx = curx + dir[i][0];
            int nexty = cury + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
            if (!visited[nextx][nexty] && grid[nextx][nexty] == '1') {
                que.push({nextx, nexty});
                visited[nextx][nexty] = true; // 只要加入队列立刻标记
            }
        }
    }

}
```
## 100. 岛屿的最大面积
- [本题的关键在于在哪里来统计岛屿的最大面积，即count++该在哪个位置](https://www.bilibili.com/video/BV1FzoyY5EXH/?vd_source=b3fd84988e8e921a37b4fa1da8d481db)
### `DFS`
```cpp
// 版本一
#include <iostream>
#include <vector>
using namespace std;
int count;
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    for (int i = 0; i < 4; i++) {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
        if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) { // 没有访问过的 同时 是陆地的
            visited[nextx][nexty] = true;
            count++;
            dfs(grid, visited, nextx, nexty);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] == 1) {
                count = 1;  // 因为dfs处理下一个节点，所以这里遇到陆地了就先计数，dfs处理接下来的相邻陆地
                visited[i][j] = true;
                dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                result = max(result, count);
            }
        }
    }
    cout << result << endl;

}
```
```cpp
// 版本二
#include <iostream>
#include <vector>
using namespace std;

int count;
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    if (visited[x][y] || grid[x][y] == 0) return; // 终止条件：访问过的节点 或者 遇到海水
    visited[x][y] = true; // 标记访问过
    count++;
    for (int i = 0; i < 4; i++) {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
        dfs(grid, visited, nextx, nexty);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));
    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] == 1) {
                count = 0; // 因为dfs处理当前节点，所以遇到陆地计数为0，进dfs之后在开始从1计数
                dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                result = max(result, count);
            }
        }
    }
    cout << result << endl;
}
```
### `BFS`
```CPP
class Solution {
private:
    int count;
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
    void bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
        queue<int> que;
        que.push(x);
        que.push(y);
        visited[x][y] = true; // 加入队列就意味节点是陆地可到达的点
        count++;
        while(!que.empty()) {
            int xx = que.front();que.pop();
            int yy = que.front();que.pop();
            for (int i = 0 ;i < 4; i++) {
                int nextx = xx + dir[i][0];
                int nexty = yy + dir[i][1];
                if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue; // 越界
                if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) { // 节点没有被访问过且是陆地
                    visited[nextx][nexty] = true;
                    count++;
                    que.push(nextx);
                    que.push(nexty);
                }
            }
        }
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == 1) {
                    count = 0;
                    bfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                    result = max(result, count);
                }
            }
        }
        return result;
    }
};
```
## 101.孤岛(上下左右都是水)的总面积
- [只要从周边找到陆地然后 通过 dfs或者bfs 将周边靠陆地且相邻的陆地都变成海洋（把陆地也标记成0），然后再去重新遍历地图 统计此时还剩下的陆地就可以了。](https://www.bilibili.com/video/BV1mmZJYRESc/?vd_source=b3fd84988e8e921a37b4fa1da8d481db)
- 本题没有必要定义visited数组了，因为不需要标记了，grid数组直接自己变了就行了
- 一些精髓
```cpp
    // 从左侧边，和右侧边 向中间遍历
    for (int i = 0; i < n; i++) {
        if (grid[i][0] == 1) bfs(grid, i, 0);
        if (grid[i][m - 1] == 1) bfs(grid, i, m - 1);
    }
    // 从上边和下边 向中间遍历
    for (int j = 0; j < m; j++) {
        if (grid[0][j] == 1) bfs(grid, 0, j);
        if (grid[n - 1][j] == 1) bfs(grid, n - 1, j);
    }
```
`完整的代码DFS`
```cpp
#include <iostream>
#include <vector>
using namespace std;
int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1}; // 保存四个方向
void dfs(vector<vector<int>>& grid, int x, int y) {
    grid[x][y] = 0;
    for (int i = 0; i < 4; i++) { // 向四个方向遍历
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        // 超过边界
        if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;
        // 不符合条件，不继续遍历
        if (grid[nextx][nexty] == 0) continue;

        dfs (grid, nextx, nexty);
    }
    return;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    // 从左侧边，和右侧边 向中间遍历
    for (int i = 0; i < n; i++) {
        if (grid[i][0] == 1) dfs(grid, i, 0);
        if (grid[i][m - 1] == 1) dfs(grid, i, m - 1);
    }
    // 从上边和下边 向中间遍历
    for (int j = 0; j < m; j++) {
        if (grid[0][j] == 1) dfs(grid, 0, j);
        if (grid[n - 1][j] == 1) dfs(grid, n - 1, j);
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) count++;
        }
    }
    cout << count << endl;
}
```
`完整的代码BFS`
```CPP
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
void bfs(vector<vector<int>>& grid, int x, int y) {
    queue<pair<int, int>> que;
    que.push({x, y});
    grid[x][y] = 0; // 只要加入队列，立刻标记
    while(!que.empty()) {
        pair<int ,int> cur = que.front(); que.pop();
        int curx = cur.first;
        int cury = cur.second;
        for (int i = 0; i < 4; i++) {
            int nextx = curx + dir[i][0];
            int nexty = cury + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
            if (grid[nextx][nexty] == 1) {
                que.push({nextx, nexty});
                grid[nextx][nexty] = 0; // 只要加入队列立刻标记
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    // 从左侧边，和右侧边 向中间遍历
    for (int i = 0; i < n; i++) {
        if (grid[i][0] == 1) bfs(grid, i, 0);
        if (grid[i][m - 1] == 1) bfs(grid, i, m - 1);
    }
    // 从上边和下边 向中间遍历
    for (int j = 0; j < m; j++) {
        if (grid[0][j] == 1) bfs(grid, 0, j);
        if (grid[n - 1][j] == 1) bfs(grid, n - 1, j);
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) count++;
        }
    }

    cout << count << endl;
}
```