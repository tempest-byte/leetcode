/*
注意到为什么这里要用到pre指针。问题是在于在链表指针赋值的时候是对指针的操作。
具体实例如下：

        ListNode* root = new ListNode(-10);
        ListNode* sec = new ListNode(-3);
        root->next = sec;
        sec = NULL;
        cout << "root->next:" << root->next << endl;
        root->next = NULL;
        cout << "root->next:" << root->next<< endl;

输出结果：
    root->next:0000026FF0A20280
    root->next:0000000000000000

因为new操作的时候申请了一块内存，并把这块内存地址赋值给sec，注意sec保存的是值！
root->next为root->next的值为sec中保存的值。所以sec之后无论怎么变化都不会和root->next产生关系。
*/

class Solution {
   public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head)
            return NULL;
        ListNode *fast = head, *slow = head, *pre = slow;
        while (fast->next && fast->next->next) {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        TreeNode* cur = new TreeNode(slow->val);
        cur->right = sortedListToBST(slow->next);
        if (slow != head) {
            pre->next = NULL;
            cur->left = sortedListToBST(head);
        }
        return cur;
    }
};

/*
讨论区有个很有意思的解答。使用中序遍历做的。
注意到他使用的是public的指针。之后每次递归操作都是在此基础上进行的
*/
class Solution {
   public:
    ListNode* list;
    int count(ListNode* node) {
        int size = 0;
        while (node) {
            ++size;
            node = node->next;
        }
        return size;
    }

    TreeNode* generate(int n) {
        if (n == 0)
            return NULL;
        TreeNode* node = new TreeNode(0);//注意此时还没有给根节点赋值，因为不知道它的值是什么
        node->left = generate(n / 2);//node->left操作将node的左子树均执行完毕，此时list的值就是root的值了。
        node->val = list->val;
        list = list->next;
        node->right = generate(n - n / 2 - 1);
        return node;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        this->list = head;
        return generate(count(head));
    }
};