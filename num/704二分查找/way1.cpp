#include <iostream>
#include <vector>//模板类，并且是一个容器类，容器（如数组、链表、集合等）的一种，它可以容纳多种类型的数据。
using namespace std;
class Solution {
public:
   int search(vector<int> &nums,int target){
      int left =0;
      int right = nums.size()-1;//size() 是容器类的成员函数,专门用于Stl容器类
      //right=nums.size()-1;是数组的最后一个元素的下标,不是数组的长度,这里使用的是左闭右闭区间
      while(left<=right){//这里必须等于，因为right代表了数组中的元素
         int middle =left+(right-left)/2;//防止溢出，等同于（left+right）/2
         if(nums[middle]>target){
            right= middle-1;//target在左区间，所以[left,middle-1]
         }else if(nums[middle]<target){
            left=middle+1;//target在右区间，所以[middle+1,right] 
         }else{
            return middle;//数组中找到目标值，直接返回下标
         }
      }
      return -1;//数组中没有目标值，返回-1
   }
  
};
//与数组相比：vector 是动态的，可以根据需要自动调整大小，而数组大小固定。
//内存分配：vector 在容量不足时会自动重新分配内存，但频繁的重新分配会影响性能。可以通过 reserve() 提前分配足够空间来优化