#include <iostream>
#include <vector>
#include <utility>
using namespace std;
class Solution {
public:
     void stringreverse(vector<char>& s) {
        for(int i=0 ,j=s.size()-1;i<s.size()/2;i++,j--){
            swap(s[i],s[j]);
        }
     }
};
int main(){
    Solution s;
    vector<char> s1={'h','e','l','l','o'};
    s.stringreverse(s1);
    for(int i=0;i<s1.size();i++){
        cout<<s1[i]<<endl;
    }
}

