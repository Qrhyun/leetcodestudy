#include <iostream>
#include <vector>
#include <string>
using namespace std;
//例如：98，一旦出现strNum[i - 1] > strNum[i]的情况（非单调递增），首先想让strNum[i - 1]--，然后strNum[i]给为9，这样这个整数就是89，即小于98的最大的单调递增整数。

class Solution {
public:
    int monotoneIncreasingDigits(int N) {
       
      string strNum=to_string(N); //将整数转换为字符串
      int len=strNum.size(); //获取字符串的长度\
      //从后往前遍历，找到第一个不满足单调递增的位置，然后将其减1，后面的数字都置为9
      //i不能为0，因为如果i为0，说明是个位数，那么就没有前一个数字了
      for(int i=len-1;i>0;i--){
         if(strNum[i-1]>strNum[i]){
             strNum[i-1]--;
             for(int j=i;j<len;j++){
                  strNum[j]='9'; //将后面的数字都置为9
             }
         }
      }
      return stoi(strNum); //将字符串转换为整数
    }
};