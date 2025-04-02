#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
 int wiggleMaxLength(vector<int> &nums){
  //1.贪心算法第一点：针对单调坡度，选择坡度的最高和最低，最高，试图尽最大努力保证后面   prediff < 0 && curdiff > 0 或者 prediff > 0 && curdiff < 0
  //2.贪心算法第二点：特殊情况：
      // - 上下坡中有平坡：选择平坡的最右面元素  (preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)
      // - 数组只有两个元素：针对序列[2,5]，可以假设为[2,2,5]，默认最右面有个峰值为1个，还有中间的2满足preDiff = 0 && curDiff > 0
    if(nums.size()<=1) return nums.size(); //如果数组长度小于等于1，直接返回数组长度
    int curDiff=0; //当前差值
    int preDiff=0; //前一个差值
    int result=1; //记录峰值个数，序列默认序列最右边有一个峰值
    for(int i=0;i<nums.size()-1;i++){
      //i从0开始，正是考虑到第二种情况
      //遍历数组，计算当前差值和前一个差值
      curDiff=nums[i+1]-nums[i];
      //preDiff=nums[i]-nums[i-1];//这里可以省去一些计算量，将前面的结果保留到后面
      //如果当前差值和前一个差值一正一负，或者当前差值为0，并且前一个差值为0，说明找到了一个峰值
      if((curDiff>0&&preDiff<=0)||(curDiff<0&&preDiff>=0)){
        result++; //峰值个数加1
        preDiff=curDiff; //只在摆动变化的时候更新preDiff
      }
    }
     //preDiff=curDiff; //更新前一个差值
     return result;
 }
};

//但是正因为情况2导致单调坡中的平坡也算了一次峰值。 单调中的平坡 不能算峰值（即摆动