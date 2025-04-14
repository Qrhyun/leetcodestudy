#include <bits/stdc++.h>
using namespace std;
//归并排序的基本实现
//归并排序是一种分治法的排序算法，它的基本思想是：将数组分成两部分，分别对这两部分进行排序，然后将排序好的两部分合并在一起，得到一个有序的数组
//归并排序的时间复杂度为O(nlogn)，空间复杂度为O(n)
//归并排序的基本实现，使用了递归和分治法
//归并排序的基本思想是：将数组分成两部分，分别对这两部分进行排序，然后将排序好的两部分合并在一起，得到一个有序的数组
//合并两个有序数组的过程是归并排序的关键步骤
void merge(vector<int> &arr,int middle,int left,int right){
    vector<int> temp(right-left+1);//临时数组，存放合并后的结果.这样原数组进行遍历和比较逻辑的处理，临时数组进行结果的存放
    int i=left,j=middle+1,k=0;//i指向左半部分的第一个元素，j指向右半部分的第一个元素，k指向临时数组的第一个元素。这样就保证传入的参数一直保持不变
    while(i<=middle&&j<=right){
        if(arr[i]<=arr[j]){
            temp[k++]=arr[i++];//将左半部分的元素放入临时数组中
        }else{
            temp[k++]=arr[j++];//将右半部分的元素放入临时数组中
        }
    }
    while(i<=middle){
        temp[k++]=arr[i++];//将左半部分的剩余元素放入临时数组中
    }
    while(j<=right){
        temp[k++]=arr[j++];//将右半部分的剩余元素放入临时数组中
    }
    for(int i=0;i<temp.size();i++){
        arr[left+i]=temp[i];//将临时数组中的元素放回原数组中
    }
}


//总体排序函数
void mergeSort(vector<int> &arr,int left,int right){
    //2.终止条件
    if(left>=right) return;//如果左指针大于等于右指针，说明已经排序完成
    //3.处理目前搜索节点出发的路径
    //划分阶段
    int middle=(left+right)/2;//划分中间位置
    mergeSort(arr,left,middle);//左边部分排序
    mergeSort(arr,middle+1,right);//右边部分排序
    //合并阶段
    merge(arr,middle,left,right);//合并两个有序数组

}
