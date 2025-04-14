//桶排序
#include <bits/stdc++.h>
using namespace std;
void bucketSort(vector<float> &nums){
    // 初始化 k = n/2 个桶，预期向每个桶分配 2 个元素
    int k=nums.size()/2;//比如4个元素，k=2，表示分成2个桶
    vector<vector<float>> buckets(k);//桶的大小为 k
    //1. 将元素分配到桶中
    for(float num:nums){
      // 输入数据范围为 [0, 1)，使用 num * k 映射到索引范围 [0, k-1]
      int i=num*k;//桶的索引,比如0.5*2=1，表示放在第2个桶中
      buckets[i].push_back(num);
    }
    //2. 对每个桶进行排序
    for(vector<float> &bucket : buckets){
        sort(bucket.begin(),bucket.end());//对每个桶进行排序，使用 STL 的 sort 函数
    }
    //3. 合并所有桶中的元素
    int index=0;//合并后的数组的索引
    for(vector<float> &bucket:buckets){
        for(float num:bucket){
            nums[index++]=num;//将桶中的元素放回原数组中
        }
    }
} 