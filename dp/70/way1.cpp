#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution{
public:
   int climbStairs(int n){
    //对于下标为0，1的元素是特例
    if(n<=1) return n;
    vector<int> dp(n+1);//保证后面的dp都是我想的指定
    dp[1]=1;
    dp[2]=2;
    for(int i=3;i<=n;i++){
      dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[n];
   }
};