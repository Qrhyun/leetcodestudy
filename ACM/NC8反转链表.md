```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct node {
  int data;
  struct node *next;
  node(int x) : data(x), next(nullptr) {}
};

struct node* init(){
  node* head = new node(1);
  node* second = new node(2);
  node* third = new node(3);
  node* fourth = new node(4);
  node* fifth = new node(5);
  head->next = second;
  second->next = third;
  third->next = fourth;
  fourth->next = fifth;
  fifth->next = nullptr;
  return head;
}

struct node *reverse(struct node *head) {
  node* pre = nullptr;
  node* cur = head;
  while (cur != nullptr) {
    node* temp = cur->next;
    cur->next = pre;
    pre = cur;
    cur = temp;
  }
  return pre;
}

int main() {
  struct node* head = init();
  cout << "Original List: ";
  for (node* temp = head; temp != nullptr; temp = temp->next) {
    cout << temp->data << " ";
  }
  cout << endl;

  head = reverse(head);

  cout << "Reversed List: ";
  for (node* temp = head; temp != nullptr; temp = temp->next) {
    cout << temp->data << " ";
  }
  cout << endl;

  // Clean up memory
  while (head != nullptr) {
    node* temp = head;
    head = head->next;
    delete temp;
  }

  return 0;
}
```
