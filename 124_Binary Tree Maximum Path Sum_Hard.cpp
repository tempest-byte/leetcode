//递归写法
class Solution {
   public:
    int maxPathSum(TreeNode* root) {
        int res = RootStart(root);
        return tmp;
    }

   private:
    int tmp = INT_MIN;
    int RootStart(TreeNode* root) {
        if (!root)
            return 0;
        int left = max(RootStart(root->left), 0);
        int right = max(RootStart(root->right), 0);
        int res = max(left, right);
        tmp = max(tmp, root->val + left + right);
        return max(res + root->val, 0);
    }
};

//其实写完了就发现是个后序遍历了。因为这道题就是先把左右子树的max支统计，然后单独记录包含此节点的支。建议先做145。
class Solution {
   public:
    int maxPathSum(TreeNode* root) {
        if (!root)
            return 0;
        int res = INT_MIN;
        TreeNode* pre = NULL;
        stack<TreeNode*> st;
        while (root) {
            st.push(root);
            root = root->left;
        }
        while (!st.empty()) {
            TreeNode* cur = st.top();
            if (cur->right == pre) {
                int left_val = (cur->left) ? cur->left->val : 0;
                int right_val = (cur->right) ? cur->right->val : 0;
                res = max(res, cur->val + left_val + right_val);
                cur->val = max(0, cur->val + max(left_val, right_val));
                st.pop();
                pre = cur;
            } else {
                cur = cur->right;
                while (cur) {
                    st.push(cur);
                    cur = cur->left;
                }
                pre = NULL;
            }
        }
        return res;
    }
};