#include <bits/stdc++.h>
using namespace std;
//快速排序的基本实现
//快速排序的基本实现，使用了递归和分治法
//快速排序是一种高效的排序算法，平均时间复杂度为O(nlogn)，最坏情况下为O(n^2)
//快速排序的核心操作是“哨兵划分”，其目标是：选择数组中的某个元素作为“基准数”，将所有小于基准数的元素移到其左侧，而大于基准数的元素移到其右侧
//快速排序的基本思想是：选择一个基准元素，将数组分成两部分，一部分比基准元素小，另一部分比基准元素大，然后递归地对这两部分进行排序

//分治
int partition(vector<int> &arr,int left,int right){
    int i=left,j=right;
    int pivot=arr[left];//选择第一个元素作为基准数
    while(i<j){
        while(i<j&&arr[j]>=pivot) j--;//从右向左找到第一个小于基准数的元素
        while(i<j&&arr[i]<=pivot) i++;//从左向右找到第一个大于基准数的元素
        swap(arr[i],arr[j]);//交换这两个元素
    }
    swap(arr[left],arr[i]);//将基准数放到正确的位置上
    return i;//返回基准数的位置
}
//递归
//1.确认递归函数和参数返回值
void quicksort(vector<int> &arr,int left,int right){
    //2.终止条件
    if(left>=right) return;//如果左指针大于等于右指针，说明已经排序完成
    //3.处理目前搜索节点出发的路径
    int prepivot=partition(arr,left,right);//划分,确定基准数的位置，确定接下来的排序范围
    //递归调用
    quicksort(arr,left,prepivot-1);//左边部分排序
    quicksort(arr,prepivot+1,right);//右边部分排序
}


int main(){
    vector<int> arr;
    int n;
    cin>>n;//输入数组的大小
    arr.resize(n);//调整数组大小
    for(int i=0;i<n;i++){
        cin>>arr[i];//输入数组的元素
    }
    quicksort(arr,0,n-1);//调用快速排序函数
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";//输出排序后的数组
    }
    
    cout<<endl;
    return 0;
}