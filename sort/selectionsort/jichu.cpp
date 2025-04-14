#include <bits/stdc++.h>
using namespace std;
//选择排序的基本实现
//选择排序是一种简单的排序算法，它的基本思想是：每一趟从待排序的数据元素中选出最小（或最大）的一个元素，存放在已排序序列的起始位置，直到所有元素均排序完毕
//选择排序的时间复杂度为O(n^2)，空间复杂度为O(1)
//选择排序的基本实现，使用了循环和交换法
void selectionSort(vector<int> &nums){
    //两层循环
    for(int i=0;i<nums.size()-1;i++){
        //外层循环控制选择排序的趟数,对于n个元素，最多需要n-1次的选择就可以
        int minIndex=i;//假设当前元素是最小值的下标
        for(int j=i+1;j<nums.size();j++){
            //内层循环控制后面比较的元素下标,从i+1开始，表示从当前元素的下一个元素开始比较
            if(nums[j]<nums[minIndex]){
                minIndex=j;//更新最小值的下标
            }
        }
        if(minIndex!=i)
        {//如果当前元素不是最小值的下标，才进行交换
        swap(nums[i],nums[minIndex]);//交换当前元素和最小值的元素的位置
        }
    }
}