class Solution {
    public:
        int minSubArrayLen(int target, vector<int>& nums) {
         int result=INT32_MAX;
         int sum=0;
         int currentlength=0;
         int i=0;
         for(int j=0;j<nums.size();j++){
            sum+=nums[j];
            while(sum>=target){
                currentlength=j-i+1;
                result=result<currentlength?result:currentlength;
                sum-=nums[i++];//精髓
            }
         }
         return result==INT32_MAX?0:result;//注意这个写法，这里面封装的if,所以是两个等于号
        }
    };