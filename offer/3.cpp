//
// Created by 15089 on 25-7-5.
// list打印链表,反转链表

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

//反转链表
ListNode *reverseList(ListNode *head) {
  ListNode *prev = nullptr;
  ListNode *curr = head;
  while (curr){
    ListNode *next = curr -> next;
    curr->next = prev;
    prev =curr;
    curr = next;
  }
  return prev; // prev will be the new head of the reversed list
}

// 从尾到头打印链表
vector<int> printListFromTailToHead(ListNode* head) {
  vector<int> result;
  while (head) {
    result.push_back(head->val);
    head = head->next;
  }
  return vector<int>(result.rbegin(), result.rend());
}

int main() {
  // 构造链表 1->2->3->4->nullptr
  ListNode* head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);

  // 反转链表
  ListNode* reversed = reverseList(head);

  // 打印反转后的链表
  ListNode* p = reversed;
  while (p) {
    cout << p->val << " ";
    p = p->next;
  }
  cout << endl;

  // 从尾到头打印链表
  vector<int> res = printListFromTailToHead(reversed);
  for (int v : res) cout << v << " ";
  cout << endl;

  // 释放内存
  while (reversed) {
    ListNode* tmp = reversed;
    reversed = reversed->next;
    delete tmp;
  }
  return 0;
}