//用一个一维数组（也可以理解是滚动数组）,可以优化点空间
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int uniquePaths(int m,int n){
        vector<int> dp(n);
        for(int i=0;i<n;i++) dp[i]=1; // 初始化第一行
        //从(1,1)开始遍历，下面i和j都是从1开始
        for(int j=1;j<m;j++){
            for(int i=1;i<n;i++){
                dp[i]+=dp[i-1]; // dp[i]表示第j行的第i列，dp[i-1]表示第j行的第i-1列
            }
        }
        return dp[n-1]; // 返回最后一行最后一列的值
    }
};
//把中间的dp[i][j]去掉了，直接用dp[i]表示第j行的第i列，dp[i-1]表示第j行的第i-1列,最后经过每行的累加，直到最后一行最后一列。
//同时第一列的最终结果在赋值初值的时候已经赋值了，所以不需要再去计算了。