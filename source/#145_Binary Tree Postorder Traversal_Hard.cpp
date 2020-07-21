//老规矩，递归就不写了。直接来栈。
class Solution {
   public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (!root)
            return res;
        TreeNode* pre = NULL;
        stack<TreeNode*> st;
        while (root) {
            st.push(root);
            root = root->left;
        }
        while (!st.empty()) {
            TreeNode* cur = st.top();
            if (cur->right == pre) {
                st.pop();
                pre = cur;
                res.push_back(cur->val);
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