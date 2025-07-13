#include <iostream>
#include <vector>
using namespace std;

//定义链表节点
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // 1.虚拟头节点的创立，以及初始化
        ListNode* temp = new ListNode(0);
        temp->next = head;
        // 2. 以一个操作节点*cur来操作，虚拟节点要保持不动
        ListNode* cur = temp;
        // 3. 删除节点
        while (cur->next != NULL) {
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        // 4. 虚拟头节点的回收以及返回头节点
        head = temp->next;
        delete temp;
        return head;
    }
};

//创建链表
ListNode *createList(vector<int> &nums) {
  if (nums.empty()) return nullptr;

  ListNode *head = new ListNode(nums[0]);
  ListNode *cur = head;
  for (int i= 1; i < nums.size(); ++i) {
    cur->next = new ListNode(nums[i]);
    cur = cur->next;
  }
}

//打印链表
void printList(ListNode *head) {
  ListNode *cur = head;
  while (cur != nullptr) {
    cout << cur->val << " ";
    cur = cur->next;
  }
  cout << endl;
}

//释放链表内存
void deleteList(ListNode *head) {
  ListNode *cur = head;
  while (cur != nullptr) {
    ListNode *tmp = cur;
    cur = cur->next;
    delete tmp;
  }
}

int main() {
  int n, val;
  cout << "请输入链表长度: ";
  cin >> n;

  vector<int> nums(n);
  cout << "请输入链表元素: ";
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  cout << "请输入要删除的元素值: ";
  cin >> val;

  //创建链表
  ListNode *head = createList(nums);

  //打印链表
  printList(head);

  //删除指定元素
  Solution s;
  head = s.removeElements(head, val);

  //打印链表
  printList(head);

  //释放链表内存
  deleteList(head);

  return 0;
}