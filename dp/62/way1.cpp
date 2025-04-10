#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int uniquePaths(int m,int n){
        vector<vector<int>> dp(m,vector<int>(n,0));
        for(int i=0;i<m;i++) dp[i][0]=1;
        for(int j=0;j<n;j++) dp[0][j]=1;
        //前面的两行已经初始化了
        //从(1,1)开始遍历，下面i和j都是从1开始
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};