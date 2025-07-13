## REAL361 链表合并

`//用stl的list实现两个有序链表的合并`

```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
   list<int> l1;
   list<int> l2;
   list<int> ls;
   //1.这里的输入写法记住
   int x;
   while(cin>>x){
    l1.push_back(x);

    //2.cin.peek()函数可以查看下一个字符,这里用来判断是否到达行末
    if(cin.peek() == '\n')
    break;
   }
   while(cin>>x){
    l2.push_back(x);
    if(cin.peek() == '\n')
    break;
   }
   //3.注意这里的auto关键字的使用，这里的类型是list<int>::iterator，即为迭代器类型
   auto it1 = l1.begin();
   auto it2 = l2.begin();
   //4. it1和*it1分别表示迭代器和迭代器指向的值
   while(it1 != l1.end()&&it2 != l2.end()){
    if(*it1<=*it2) {
        ls.push_back(*it1);
        ++it1;
    }else{
        ls.push_back(*it2);
        ++it2;
    }
   }
   while(it1 != l1.end()){
    ls.push_back(*it1);
    ++it1;
   }
   while(it2 != l2.end()){
    ls.push_back(*it2);
    ++it2;
   }
   /*auto it = ls.begin();
   while(it != ls.end()) {
    cout<<*it<<' ';
    ++it;
   }*/
   for(auto e:ls) {
    cout << e << ' ';
   }
   return 0;
}
// 64 位输出请用 printf("%lld")
```

`用vector`

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    vector<int> in1, in2;
    int num = 0;
    while(cin>>num) {
        in1.push_back(num);
        if(cin.get() == '\n')
        break;
    }
    while(cin >> num){
        in2.push_back(num);
        if(cin.get() == '\n')
        break;
    }
    for(auto a : in2) {
        in1.push_back(a);
    }
    sort(in1.begin(), in1.end());
    for(auto a : in1) {
        cout << a << " ";
    }
    return 0;
}
```
