/*
日常写法。每个节点值相等，再递归操作左右子节点是否相等。
*/
class Solution {
   public:
    bool isSameTree(TreeNode* p, TreeNode* q) { return isSameNode(p, q); }

   private:
    bool isSameNode(TreeNode* p, TreeNode* q) {
        if (!p)
            return !q;
        else if (!q)
            return !p;
        else {
            if (p->val == q->val)
                return isSameNode(p->left, q->left) &&
                       isSameNode(p->right, q->right);
            return false;
        }
    }
};