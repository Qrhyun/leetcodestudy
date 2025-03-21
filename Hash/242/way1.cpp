#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    bool isAnagram(string s,string t){
        int record[26]={0};
        for(int i=0;i<s.size();i++){
            record[s[i]-'a']++;//s[i]-'a'是s[i]的ASCII码减去'a'的ASCII码，得到s[i]在字母表中的位置
        }
        for(int i=0;i<t.size();i++){
            record[t[i]-'a']--;
        }
        for(int i=0;i<26;i++){
            if(record[i]!=0){
                return false;
            }
     
        }
        return true;
    }


};