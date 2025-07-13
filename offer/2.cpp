//
// Created by 15089 on 25-7-5.
// string替换空格
#include <iostream>
using namespace std;

char * replaceSpace(char *str, int length) {
  if (str == nullptr || length <= 0) {
    return str;
  }
  int spaceCount = 0,totalLength = length;
  //统计空格个数
  for (int i = 0; i < length; ++i) {
    if (str[i] == ' ') {
      spaceCount++;
    }
  }
  totalLength += spaceCount * 2; // 每个空格替换为"%20"，增加了两个字符
  //替换
  for (int i =length -1; i > 0 && totalLength != i; --i) {
    if (str[i] != ' ') {
      str[--totalLength] = str[i];
    }else if (str[i] == ' ') {
      str[--totalLength] = '0';
      str[--totalLength] = '2';
      str[--totalLength] = '%';
    }
  }
  return str;
}

int main() {
  char str[100] = "We are happy.";
  int length = 15; // 字符串长度
  cout << "Original string: " << str << endl;
  char *result = replaceSpace(str, length);
  cout << "Replaced string: " << result << endl;
  return 0;
}