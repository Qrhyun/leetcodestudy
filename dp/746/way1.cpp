//dp[i]的定义：到达第i台阶所花费的最少体力为dp[i]
//可以有两个途径得到dp[i]，一个是dp[i-1] 一个是dp[i-2]。
//dp[i - 1] 跳到 dp[i] 需要花费 dp[i - 1] + cost[i - 1]。
//dp[i - 2] 跳到 dp[i] 需要花费 dp[i - 2] + cost[i - 2]。
#include <iostream>
#include <vector>
using namespace std;
class Solution{
public:
    int minCostClimbingStairs(vector<int> & cost){
      vector<int> dp(cost.size()+1);//最后一节台阶也算
      dp[0]=0;
      dp[1]=0;
      for(int i=2;i<=cost.size();i++){
        dp[i]=min(dp[i-1]+cost[i-1],dp[i-2]+cost[i-2]);
      }
      return dp[cost.size()];
    }
};