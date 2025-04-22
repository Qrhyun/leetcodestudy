class Solution {
    public:
        int minSubArrayLen(int target, vector<int>& nums) {
            int m = INT32_MAX;
            for(int i=0;i<nums.size();i++){
                int sum=0;
                for (int j=i;j<nums.size();j++){
                    sum+=nums[j];
                    if(sum>=target){
                        int currentlength=j-i+1;
                        m=m<currentlength?m:currentlength;
                        break;
                    }
                }
            }
          if(m==INT32_MAX){
            return 0;
          }else{
            return m;
          }
        }
    };