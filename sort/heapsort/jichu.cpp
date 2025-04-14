#include <bits/stdc++.h>
using namespace std;
//堆排序的基本实现
//堆排序是一种基于比较的排序算法，它的基本思想是：将待排序的元素构建成一个大顶堆或小顶堆，然后将堆顶元素与最后一个元素交换位置，再将剩下的元素重新调整为堆，直到所有元素都排好序
//堆排序的时间复杂度为O(nlogn)，空间复杂度为O(1)
//堆排序的基本实现，使用了循环和交换法
/* 堆的长度为 n ，从节点 i 开始，从顶至底堆化 */
void  siftDown(vector<int> &arr,int i,int n){
    //这个前提是已经是堆化过后的树了，然后仅仅要把根节点的值进行调整
    while(true){
       int l=s*i+1;//左子节点
       int r=s*i+2;//右子节点
       int ma=i;//假设当前节点是最大值的下标
       if(l<n&&arr[l]>arr[ma]) ma=l;//如果左子节点存在且大于当前节点，更新最大值的下标
       if(r<n&&arr[r]>arr[ma]) ma=r;//如果右子节点存在且大于当前节点，更新最大值的下标
       if(ma==i) break;//如果最大值的下标没有变化，说明已经堆化完成，退出循环
       else{
        swap(arr[i],arr[ma]);//交换当前节点和最大值的节点的位置
        i=ma;//更新当前节点为最大值的节点
       }
    }
}


//堆排序的总体函数

void heapSort(vector<int>& cur){
    //构建大顶堆
    /*int i = cur.size()/2 - 1 是为了找到完全二叉树中最后一个非叶子节点的索引*/
    for(int i=cur.size()/2-1;i>=0;i--){
        siftDown(cur,cur.size(),i);//从最后一个非叶子节点开始堆化
    }
    //排序
    for(int i=cur.size()-1;i>0;i--){
        swap(cur[0],cur[i]);//交换堆顶元素和最后一个元素的位置
        siftDown(cur,0,i);//重新调整堆
    }
}