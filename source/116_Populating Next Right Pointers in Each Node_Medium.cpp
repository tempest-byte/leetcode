/*
不过这道题我很纳闷为什么时间上这么慢，也没看到网上有更快的解法啊。。
用队列做其实就和之前很相似了。但不是常数空间。
使用node指针来做。head存储上一层的node头指针，由于上一层已经连接完毕，所以可以根据上一层来导出本层。
但是问题在于对于每层指针都相当于调用两次。一次是new的时候，另一次是根据其对下一层查找的时候。
*/
class Solution {
   public:
    Node* connect(Node* root) {
        if (!root)
            return root;
        Node *head = root, *cur, *new_head;
        while (head->left) {
            new_head = head->left;
            cur = head->right;  
            head->left->next = cur;
            while (head->next) {
                head = head->next;
                cur->next = head->left;
                cur = head->right;
                head->left->next = cur;
            }
            head = new_head;
        }
        return root;
    }
};

/*
递归的方法，简单但是没想出来
*/
class Solution {
   public:
    Node* connect(Node* root) {
        if (!root)
            return NULL;
        if (root->left)
            root->left->next = root->right;
        if (root->right)
            root->right->next = root->next ? root->next->left : NULL;
        connect(root->left);
        connect(root->right);
        return root;
    }
};