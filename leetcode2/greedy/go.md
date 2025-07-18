## 455.分发饼干
- 局部最优就是大饼干喂给胃口大的，充分利用饼干尺寸喂饱一个，全局最优就是喂饱尽可能多的小孩
- 使用贪心策略，先将饼干数组和小孩数组排序.然后从后向前遍历小孩数组，用大饼干优先满足胃口大的，并统计满足小孩数量。
```cpp
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int index = s.size() - 1;// 饼干数组的下标
        int result = 0;
        //人可以不用全部都有饼干，但是饼干最好全分出去
        for(int i = g.size() - 1; i >= 0; i--){
            if(index >= 0 && s[index] >= g[i]) {
                result++;
                index--;
            }
        }
        return result;
    }
};
```
## 1005.K次取反后最大化的数组和
- 将数组按照绝对值大小从大到小排序，注意要按照绝对值的大小
- 贪心的思路，局部最优：让绝对值大的负数变为正数，当前数值达到最大，整体最优：整个数组和达到最大。
- 那么如果将负数都转变为正数了，K依然大于0，此时的问题是一个有序正整数序列，如何转变K次正负，让 数组和 达到最大。那么又是一个贪心：局部最优：只找数值最小的正整数进行反转，当前数值和可以达到最大（例如正整数数组{5, 3, 1}，反转1 得到-1 比 反转5得到的-5 大多了），全局最优：整个 数组和 达到最大。
- 这么一道简单题，就用了两次贪心！
```cpp
class Solution {
public:
    static bool cmp (int a, int b) {
        return abs(a) > abs(b);
    }
    int largestSumAfterKNegations(vector<int>& A, int k) {
        sort(A.begin(), A.end(), cmp);
        for(int i = 0; i < A.size(); i++) {
            if(A[i] < 0 && k > 0) {
                A[i] *= -1;//转化为正数
                k--;
            }
        }
        //如果k还剩奇数
        if(k % 2 == 1) A[A.size() - 1] *= -1;
        int result = 0;
        for(int a : A) result += a;
        return result;
    }
};
```

## 860.柠檬水找零
- 有如下三种情况：
> 情况一：账单是5，直接收下。
> 情况二：账单是10，消耗一个5，增加一个10
> 情况三：账单是20，优先消耗一个10和一个5，如果不够，再消耗三个5
- 发现 情况一，情况二，都是固定策略，都不用我们来做分析了，而唯一不确定的其实在情况三。因为美元10只能给账单20找零，而美元5可以给账单10和账单20找零，美元5更万能！所以局部最优：遇到账单20，优先消耗美元10，完成本次找零。全局最优：完成全部账单的找零
```cpp
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0, tewnty = 0;
        for (int bill : bills) {
            if (bill == 5)
                five++;

            if (bill == 10) {
                if (five <= 0)
                    return false;
                ten++;
                five--;
            }

            if (bill == 20) {
                // 在10和5都存在的前提下，优先消耗10美元，因为5美元的找零用处更大，能多留着就多留着
                if (five > 0 && ten > 0) {
                    five--;
                    ten--;
                    tewnty++;
                } else if (five >= 3) {
                    five -= 3;
                    tewnty++;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};
```