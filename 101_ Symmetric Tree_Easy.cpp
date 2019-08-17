/*
递归写法。每次对称比较。
*/
class Solution {
   public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return Sym(root->left, root->right);
    }

   private:
    bool Sym(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2)
            return true;
        else if (root1 && root2)
            return (root1->val == root2->val &&
                    Sym(root1->left, root2->right) &&
                    Sym(root1->right, root2->left));
        else
            return false;
    }
};

/*
队列写法。new两个队列，需要比较的位置分别放入两个队列。
*/
class Solution {
   public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode*> q1, q2;
        q1.push(root->left);
        q2.push(root->right);
        TreeNode *tmp1, *tmp2;
        while (!q1.empty()) {
            tmp1 = q1.front();
            tmp2 = q2.front();
            q1.pop();
            q2.pop();
            if (!tmp1 && !tmp2)
                continue;
            else if (tmp1 && tmp2) {
                if (tmp1->val != tmp2->val) return false;
                q1.push(tmp1->left);
                q1.push(tmp1->right);
                q2.push(tmp2->right);
                q2.push(tmp2->left);
            } else
                return false;
        }
        return true;
    }
};