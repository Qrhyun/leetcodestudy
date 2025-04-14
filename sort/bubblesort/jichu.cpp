#include<bits/stdc++.h>
using namespace std;
//冒泡排序的基本实现
//冒泡排序是一种简单的排序算法，它重复地遍历要排序的元素，比较相邻的元素，如果它们的顺序错误就把它们交换过来。遍历元素的工作是重复地进行直到没有再需要交换，也就是该元素已经排序完成
//冒泡排序的时间复杂度为O(n^2)，空间复杂度为O(1)
//冒泡排序的基本思想是：从头到尾遍历数组，比较相邻的元素，如果前一个元素大于后一个元素，就交换它们的位置。这样一趟下来，最大的元素就会“冒泡”到数组的末尾。然后再对剩下的元素进行同样的操作，直到整个数组有序
//冒泡排序的基本实现，使用了循环和交换法
void bubbbleSort(vector<int> &nums){
    //两层循环
    for(int i=0;i<nums.size()-1;i++){
        //外层循环控制排序的趟数,对于n个元素，最多需要n-1趟排序
        for(int j=0;j<nums.size()-1-i;j++){
          ////内层循环控制每一趟排序的次数,对于n个元素，最多需要n-1-i次比较
           if(nums[j]>nums[j+1]){
            swap(nums[j],nums[j+1]);//交换两个元素的位置
           }
        }
    }
}


//优化
//如果在某一趟排序中没有发生交换，说明数组已经有序，可以提前结束排序
//优化后的冒泡排序，使用了标志位来判断是否发生交换
void bubbbleSort2(vector<int> &nums){
    for(int i=0;i<nums.size()-1;i++){
        bool flag=false;//标志位，表示是否发生交换
        for(int j=0;j<nums.size()-1-i;j++){
            if(nums[j]>nums[j+1]){
                swap(nums[j],nums[j+1]);//交换两个元素的位置
                flag=true;//发生交换，标志位设为true
            }
        }
        if(!flag) break;//如果没有发生交换，提前结束排序
    }
}