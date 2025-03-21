//设置一个虚拟头结点在进行移除节点操作
class Solution {
    public:
        ListNode* removeElements(ListNode* head, int val) {
            ListNode *virtualHead=new ListNode(0);//设置一个虚拟头节点，并使其值为0
            virtualHead->next=head;//将虚拟头结点指向head，这样方便后面做删除操作
            ListNode* cur = virtualHead;
            while(cur->next != NULL){
                if(cur->next->val ==val){
                    ListNode* tmp =cur ->next;
                    cur->next=cur->next->next;
                    delete tmp;
                }else{
                    cur=cur->next;
                }
            }
            head=virtualHead->next;//重新指向新的头节点（包括了删除头节点的情况）
            delete virtualHead;//把临时的删掉
            return head;
        }
    };