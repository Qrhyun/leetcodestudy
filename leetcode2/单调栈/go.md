# 单调栈
- 通常是一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置，此时我们就要想到可以用单调栈了。时间复杂度为O(n)。
- 单调栈的本质是空间换时间，因为在遍历的过程中需要用一个栈来记录右边第一个比当前元素高的元素，优点是整个数组只需要遍历一次。
- 更直白来说，就是用一个栈来记录我们遍历过的元素，因为我们遍历数组的时候，我们不知道之前都遍历了哪些元素，以至于遍历一个元素找不到是不是之前遍历过一个更小的，所以我们需要用一个容器（这里用单调栈）来记录我们遍历过的元素。
- 单调栈里面放什么：单调栈里只需要存放元素的下标i就可以了，如果需要使用对应的元素，直接T[i]就可以获取。
- 单调栈里面的元素是递增的，还是递减的？：即：如果求一个元素右边第一个更大元素，单调栈就是递增的，如果求一个元素右边第一个更小元素，单调栈就是递减的。
## 739.每日温度
```md
情况一：当前遍历的元素T[i]小于栈顶元素T[st.top()]的情况
情况二：当前遍历的元素T[i]等于栈顶元素T[st.top()]的情况
情况三：当前遍历的元素T[i]大于栈顶元素T[st.top()]的情况
```
- 本题注意元素是temperatures[st.top()]，而不是栈顶元素T[st.top()]
- 本题注意一开始要把0压入栈，因为第一个元素在栈里不存在左边的元素。
- 本题注意`if (temperatures[i] <= temperatures[st.top()])`必须在`while`循环的前面，并且while循环里面必须加上`!st.empty()`。因为存在一种情况，当弹栈弹的栈里面没有了元素的时候，这时候必然要`st.push(i)`,不能走`temperatures[i] <= temperatures[st.top()]`比较才push
```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size(), 0);
        stack<int> st; // 单调栈
        st.push(0);    // 先把索引0压入
        for (int i = 1; i < temperatures.size(); i++) {
            if (temperatures[i] <= temperatures[st.top()]) {
                st.push(i);
            } else {
                while (!st.empty() &&
                       temperatures[i] > temperatures[st.top()]) {
                    result[st.top()] = i - st.top();
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }
};
```
## 496.下一个更大元素 I
- 本题则是说nums1 是 nums2的子集，找nums1中的元素在nums2中下一个比当前元素大的元素。
- 在遍历nums2的过程中，我们要判断nums2[i]是否在nums1中出现过，因为最后是要根据nums1元素的下标来更新result数组。注意题目中说是两个没有重复元素 的数组 nums1 和 nums2。没有重复元素，我们就可以用map来做映射了。根据数值快速找到下标，还可以判断nums2[i]是否在nums1中出现过。（这就是本题加的额外业务逻辑）
- 栈头到栈底的顺序，要从小到大，也就是保持栈里的元素为递增顺序。只要保持递增，才能找到右边第一个比自己大的元素。
```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        vector<int> result(nums1.size(), -1);
        if(nums1.size() == 0) return result;//先处理特殊情况
        unordered_map<int, int> umap;// key:下标元素，value：下标
        for(int i = 0; i < nums1.size(); i++) {
            umap[nums1[i]] = i;
        }
        st.push(0);
        //遍历参考数组
        for(int i = 1; i < nums2.size(); i++) {
            if(nums2[i] <= nums2[st.top()]) {
                st.push(i);
            }else{
                while(!st.empty() && nums2[i] > nums2[st.top()]) {
                    if(umap.count(nums2[st.top()]) > 0) {
                        //因为找到了比st.top()大的元素，那么如果st.top()确实存在，就记录下来
                        //result[i++] = i - st.top();注意这里不是求下标，而是求值的差
                        //result[i++] = nums2[i] - nums[st.top()];这个也是不可以的，因为一个数的相对位置在两个数组种的顺序是不一致的
                        int index = umap[nums2[st.top()]];// 根据map找到nums2[st.top()] 在 nums1中的下标,这就是上面map里面选择索引作为value的原因
                        result[index] = nums2[i];
                        //st.pop();这句不可以放在这里，要放在参考数组的操作作用域内 
                    }
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }
};
```
## 503.下一个更大元素II
- 循环数组
- 可以直接把两个数组拼接在一起，然后使用单调栈求下一个最大值
```cpp
// 版本一
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        // 拼接一个新的nums,用insert
        vector<int> nums1(nums.begin(), nums.end());
        nums.insert(nums.end(), nums1.begin(), nums1.end());
        // 用新的nums大小来初始化result
        vector<int> result(nums.size(), -1);
        if (nums.size() == 0) return result;

        // 开始单调栈
        stack<int> st;
        st.push(0);
        for (int i = 1; i < nums.size(); i++) { 
            if (nums[i] < nums[st.top()]) st.push(i); 
            else if (nums[i] == nums[st.top()]) st.push(i);
            else { 
                while (!st.empty() && nums[i] > nums[st.top()]) {
                    result[st.top()] = nums[i];
                    st.pop();
                }
                st.push(i);
            }
        }
        // 最后再把结果集即result数组resize到原数组大小
        result.resize(nums.size() / 2);
        return result;
    }
};
```
- 这种写法确实比较直观，但做了很多无用操作，例如修改了nums数组，而且最后还要把result数组resize回去。resize倒是不费时间，是O(1)的操作，但扩充nums数组相当于多了一个O(n)的操作。其实也可以不扩充nums，而是在遍历的过程中模拟走了两边nums。
- `for (int i = 1; i < nums.size() * 2; i++)`
```cpp
// 版本二
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> result(nums.size(), -1);
        if (nums.size() == 0) return result;
        stack<int> st;
        st.push(0);
        for (int i = 1; i < nums.size() * 2; i++) { 
            // 模拟遍历两边nums，注意一下都是用i % nums.size()来操作
            if (nums[i % nums.size()] < nums[st.top()]) st.push(i % nums.size());
            else if (nums[i % nums.size()] == nums[st.top()]) st.push(i % nums.size()); 
            else {
                while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                    result[st.top()] = nums[i % nums.size()];
                    st.pop();
                }
                st.push(i % nums.size());
            }
        }
        return result;
    }
};
```
## 42.接雨水
todo......
## 84.柱状图中最大的矩形
todo。。。。