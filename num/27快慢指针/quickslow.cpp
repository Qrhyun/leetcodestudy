//快慢指针
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int quickslow(vector<int>& nums ,int target) {
       int slow=0;
       for(int fast=0;fast<nums.size();fast++){
            if(nums[fast]!=target){
                nums[slow++]=nums[fast];//这里注意是a++,先赋值再自增 
            }        
       } 
       return slow;
    }

};