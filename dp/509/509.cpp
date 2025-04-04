//斐波那契数列
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int fib(int n){
      //对于下标为0，1的元素是特例
      if(n<2){
        return n;
      }
      //创建一个数组
      int dp[2];
      dp[0]=0;
      dp[1]=1;
      //从初始开始
      for(int i=2;i<=n;i++){
        int sum=dp[0]+dp[1];
        dp[0]=dp[1];
        dp[1]=sum;
      }
      return dp[1];
    }
};