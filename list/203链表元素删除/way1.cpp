//删除链表中的一个元素
//法一：在原链表本身上进行删除
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//链表的定义，实际上是链表节点的定义
struct  ListNode{
    int val;
    ListNode* next;
    ListNode():val(0),next(nullptr){}//初始化列表
    ListNode(int x):val(x),next(nullptr){}
    ListNode(int x,ListNode* next):val(x),next(next){}
};
class Solution{
public:
    //删除头节点
    ListNode* removeElements(ListNode* head,int val){
        //删除头节点
        while(head!=NULL&&head->val==val){
          ListNode* tmp=head;
          head =head->next;
          delete tmp;//用于释放通过 new 操作符动态分配的内存，是C++内存管理的重要组成部分
       } 
       //删除非头节点
       ListNode* cur=head;//防止移动头节点
       while(cur!=NULL&&cur->next!=NULL){
          if(cur->next->val==val){
            ListNode* tmp=cur->next;
            cur->next=cur->next->next;
            delete tmp;
          }else{
            cur=cur->next;
          }
       }
       return head;//返回头节点
    }
};
//辅助函数，根据数组创建链表,也就是建立链表的过程
//创建链表的过程，就是不断地创建节点，然后将节点连接起来
ListNode* numtolist(const vector<int>& nums){
   if(nums.empty()){
      return nullptr;
   }
   ListNode* head=new ListNode(nums[0]);//创建头节点,使用new关键字借助结构体创建一个节点
   ListNode* cur=head;//创建一个指针指向头节点
   for(int i=1;i<nums.size();i++){
        cur->next=new ListNode(nums[i]);//创建一个新节点
        cur=cur->next;//将指针移动到下一个节点
   }
   return head;//返回头节点

}
//辅助函数，将链表转换为数组,符合题目的输出形式，也就是将链表输出为数组，并且在输出的同时释放内存
vector<int> listtonum(ListNode* head){
    vector<int> nums;
    while(head!=nullptr){
        nums.push_back(head->val);//push_back 用于向 std::vector 的末尾添加一个元素。
        ListNode* tmp=head;
        head=head->next;
        delete tmp;
    }
    return nums;//这里只能返回数组，所以[]的输出放在main函数中
}

int main(){
    Solution solution;//创建一个对象

    //输入逻辑
    cout<<"请输入一个数组:"<<endl;
    string input;
    getline(cin,input);//输入一个字符串是 C++ 中用于从输入流中读取一整行字符串的函数，定义在 <string> 头文件中

    string input;
    getline(cin, input);

    // 解析输入
    size_t headStart = input.find("[");
    size_t headEnd = input.find("]");
    string headStr = input.substr(headStart + 1, headEnd - headStart - 1);
    size_t valPos = input.find("val = ");
    int val = stoi(input.substr(valPos + 6));

    // 将输入的链表字符串转换为 vector<int>
    vector<int> values;
    size_t pos = 0;
    while ((pos = headStr.find(",")) != string::npos) {
        values.push_back(stoi(headStr.substr(0, pos)));
        headStr.erase(0, pos + 1);
    }
    if (!headStr.empty()) {
        values.push_back(stoi(headStr));
    }

    // 创建链表
    ListNode* head = numtolist(values);

    // 删除指定值的节点
    head = solution.removeElements(head, val);

    // 转换为数组并输出结果
    vector<int> result = listtonum(head);
    cout << "输出：[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i != result.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    return 0;
}