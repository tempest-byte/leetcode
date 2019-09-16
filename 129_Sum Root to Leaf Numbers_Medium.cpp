//没什么好说的把，常规题目。用BFS做的，当然也可以用DFS做。
class Solution {
   public:
    int sumNumbers(TreeNode* root) {
        if (!root)
            return 0;
        queue<TreeNode*> qu;
        qu.push(root);
        int res = 0;
        while (!qu.empty()) {
            for (int i = qu.size() - 1; i >= 0; i--) {
                TreeNode* cur = qu.front();
                qu.pop();
                if (!cur->left && !cur->right)
                    res += cur->val;
                else {
                    if (cur->left) {
                        qu.push(cur->left);
                        cur->left->val += cur->val * 10;
                    }
                    if (cur->right) {
                        qu.push(cur->right);
                        cur->right->val += cur->val * 10;
                    }
                }
            }
        }
        return res;
    }
};