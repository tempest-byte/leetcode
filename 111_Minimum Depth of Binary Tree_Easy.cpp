class Solution {
   public:
    int minDepth(TreeNode* root) {
        queue<TreeNode*> qu;
        if (!root)
            return 0;
        int res = 0;
        qu.push(root);
        while (!qu.empty()) {
            res++;
            for (int i = qu.size() - 1; i >= 0; i--) {
                TreeNode* cur = qu.front();
                qu.pop();
                if (!cur->left && !cur->right)
                    return res;
                else {
                    if (cur->left)
                        qu.push(cur->left);
                    if (cur->right)
                        qu.push(cur->right);
                }
            }
        }
        return res;
    }
};