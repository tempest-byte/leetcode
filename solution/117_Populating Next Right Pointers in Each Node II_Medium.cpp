/*
和116题没什么区别，只不过需要加点条件判断一下。
*/
class Solution {
   public:
    Node* connect(Node* root) {
        if (!root)
            return root;
        Node *head = root, *cur, *new_head;
        while (head) {
            while (head && !head->left && !head->right)
                head = head->next;
            if (!head)
                break;
            new_head = head->left ? head->left : head->right;
            if (head->left && head->right)
                head->left->next = head->right;
            cur = head->right ? head->right : head->left;
            while (head->next) {
                head = head->next;
                if (!head->left && !head->right)
                    continue;
                if (head->left && head->right)
                    head->left->next = head->right;
                cur->next = head->left ? head->left : head->right;
                cur = head->right ? head->right : head->left;
            }
            head = new_head;
        }
        return root;
    }
};
/*
思路差不多，不过更简单。使用了dummy这个先驱节点。用来统一情况。
https://www.cnblogs.com/grandyang/p/4290148.html
*/
class Solution {
   public:
    Node* connect(Node* root) {
        Node *dummy = new Node(0, NULL, NULL, NULL), *cur = dummy, *head = root;
        while (root) {
            if (root->left) {
                cur->next = root->left;
                cur = cur->next;
            }
            if (root->right) {
                cur->next = root->right;
                cur = cur->next;
            }
            root = root->next;
            if (!root) {
                cur = dummy;
                root = dummy->next;
                dummy->next = NULL;
            }
        }
        return head;
    }
};