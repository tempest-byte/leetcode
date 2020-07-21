/*
直接用栈做。唯一需要注意的一点就是要先放右节点，再放左节点。这样才能保证是前序遍历。
*/
class Solution {
   public:
    void flatten(TreeNode* root) {
        if (!root)
            return;
        stack<TreeNode*> st;
        st.push(root);
        TreeNode* pre = new TreeNode(0);
        while (!st.empty()) {
            TreeNode* cur = st.top();
            st.pop();
            pre->right = cur;
            pre->left = NULL;
            if (cur->right)
                st.push(cur->right);
            if (cur->left)
                st.push(cur->left);
            pre = pre->right;
        }
    }
};

/*
有意思的一种解法，把左子树完整放在root和右子树之间。然后此时root=root->right，循环操作
*/
class Solution {
   public:
    void flatten(TreeNode* root) {
        TreeNode* cur = root;
        while (cur) {
            if (cur->left) {
                TreeNode* p = cur->left;
                while (p->right)
                    p = p->right;
                p->right = cur->right;
                cur->right = cur->left;
                cur->left = NULL;
            }
            cur = cur->right;
        }
    }
};