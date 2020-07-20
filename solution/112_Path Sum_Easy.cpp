/*
好傻啊。总是喜欢用额外的变量去判断是否满足条件。只需要传递一个int就可以了。
之前是bool helper(root,sum,res){res += root->val;……}
*/
class Solution {
   public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root)
            return false;
        return helper(root, sum);
    }

   private:
    bool helper(TreeNode* root, int sum) {
        sum -= root->val;
        if (!root->left && !root->right) {
            return sum == 0;
        }
        if (root->left)
            if (helper(root->left, sum))
                return true;
        if (root->right)
            if (helper(root->right, sum))
                return true;
        return false;
    }
};

/*
如果破坏类的完整性，可以利用TreeNode->val的值进行运算。
https://www.cnblogs.com/grandyang/p/4036961.html
*/
class Solution {
   public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root)
            return false;
        stack<TreeNode*> st{{root}};
        while (!st.empty()) {
            TreeNode* t = st.top();
            st.pop();
            if (!t->left && !t->right) {
                if (t->val == sum)
                    return true;
            }
            if (t->right) {
                t->right->val += t->val;
                st.push(t->right);
            }
            if (t->left) {
                t->left->val += t->val;
                st.push(t->left);
            }
        }
        return false;
    }
};