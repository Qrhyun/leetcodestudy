//两个维度权衡问题。两步局部最优推出全局最优。同时比较两个局部最优选择最优
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int candy(vector<int>& ratings){
      int result=0;
      vector<int> candyNum(ratings.size(),1);//初始化每个孩子的糖果数为1
      //从左往右遍历，保证右边的孩子比左边的孩子的糖果数多，如果右边的孩子比左边的孩子的评分高，那么右边的孩子的糖果数就比左边的孩子的糖果数多1
      for(int i=1;i<ratings.size();i++){
        //这里是从1开始的，因为比较的是i和i-1，所以i不能为0
        if(ratings[i]>ratings[i-1]){
          candyNum[i]=candyNum[i-1]+1;
        }
      }
      result+=candyNum[ratings.size()-1];
      //从右往左遍历，保证左边的孩子比右边的孩子的糖果数多，如果左边的孩子比右边的孩子的评分高，那么左边的孩子的糖果数就比右边的孩子的糖果数多1
      for(int i=ratings.size()-2;i>=0;i--){
        //这里是从ratings.size()-2开始的，因为比较的是i和i+1，所以i不能为ratings.size()-1
        if(ratings[i]>ratings[i+1]){
          candyNum[i]=max(candyNum[i],candyNum[i+1]+1);
        }
        result+=candyNum[i];
      }
      return result;
    }
};
