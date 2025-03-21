#include <algorithm>
#include <cmath>//abs()
#include <iostream>
#include <vector>
using namespace std;
//那么数组平方的最大值就在数组的两端，不是最左边就是最右边，不可能是中间
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
       int k=nums.size()-1;
       vector<int> result(nums.size(),0);//初始化一个数组，大小为nums.size(),并且全部初始化为0
       for(int i=0,j=nums.size()-1;i<=j;){
        //注意这里的等号，因为当i=j的时候，也需要比较一次,对应后面的else的条件
           if(abs(nums[i])<abs(nums[j])){
              result[k--]=nums[j]*nums[j];//从后往前赋值
              j--; 
           }else{
            result[k--]=nums[i]*nums[i];
            i++;
           }
       }
        
    }
};
