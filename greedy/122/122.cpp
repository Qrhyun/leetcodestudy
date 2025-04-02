//只有一只股票！当前只有买股票或者卖股票的操作想获得利润至少要两天为一个交易单元。
//假如第 0 天买入，第 3 天卖出，那么利润为：prices[3] - prices[0]。相当于(prices[3] - prices[2]) + (prices[2] - prices[1]) + (prices[1] - prices[0])。此时就是把利润分解为每天为单位的维度，而不是从 0 天到第 3 天整体去考虑！
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& price){
        int result=0;
        //从前往后遍历，找出每一天的价格和前一天的价格的差值，如果差值大于0，则说明可以获得利润，开始赋值为1，是因为利润至少要两天为一个交易单元。
        for(int i=1;i<price.size();i++){
           result+=max(price[i]-price[i-1],0);
        }
        return result;
    }
};