//有障碍的话，其实就是标记对应的dp table（dp数组）保持初始值(0)就可以了。
//初始化的时候，但如果(i, 0) 这条边有了障碍之后，障碍之后（包括障碍）都是走不到的位置了，所以障碍之后的dp[i][0]应该还是初始值0。障碍前面的还是和之前一样赋初值为1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
   int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid){
    //由于没有给出m和n的值，所以需要从obstacleGrid中获取
    int m=obstacleGrid.size();
    int n=obstacleGrid[0].size();
    //这句可以不写if(obstacleGrid[0][0]==1 || obstacleGrid[m-1][n-1]==1) return 0; // 如果起点或者终点有障碍，直接返回0
    vector<vector<int>> dp(m,vector<int>(n,0));//1.初始化dp数组
    //2.初始化第一行和第一列
    /*不能这么写，因为如果第一行或者第一列有障碍的话，后面的都不能走了，所以要从障碍开始后面的都要保持为0，这是一个截至条件
    for(int i=0;i<m;i++){
        if(obstacleGrid[i][0]==0){
            dp[i][0]=1;
        }
    }
    */
    for(int i=0;i<m&&obstacleGrid[i][0]==0;i++){
        dp[i][0]=1; // 初始化第一列
    }
    for(int j=0;j<n&&obstacleGrid[0][j]==0;j++){
        dp[0][j]=1; // 初始化第一行
    }
    //3&4.确定遍历顺序，确定推导公式，从(1,1)开始遍历，下面i和j都是从1开始
    //这里i和j都是从1开始，所以关于i=0和j=0且有障碍物的时候，要在上面赋初值的时候写上
    for(int i=1;i<m;i++){
        for(int j=1;j<n;j++){
            if(obstacleGrid[i][j]==1){
                continue; // 如果当前位置有障碍，跳过
            }
            //如果当前位置没有障碍，dp[i][j]的值等于上面和左边的值之和
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
        }
    }
    return dp[m-1][n-1]; // 返回最后一行最后一列的值
   }
};
