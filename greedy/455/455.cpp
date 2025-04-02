#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int findContentChildren(vector<int>& g,vector<int>& s){
      sort(g.begin(),g.end());
      sort(s.begin(),s.end());
      int index=s.size()-1;//饼干的下标
      int result=0;
      //必须是是先遍历的胃口，在遍历的饼干，因为是从后往前遍历，这样才能保证每个孩子都能得到满足
      for(int i=g.size()-1;i>=0;i--){
        if(index>=0&&s[index]>=g[i]){
          result++;
          index--;
        }//这里不能第一次遇到分配不出去的情况，就跳出循环，因为可能后面的孩子也分配不出去，所以要继续循环
      }
      return result;

    }
};