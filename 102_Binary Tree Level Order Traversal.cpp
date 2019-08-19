/*
自己写的思路一样，但是没有大佬的简洁。参照的大佬的解法https://www.cnblogs.com/grandyang/p/4051321.html
陷入思维定势了，总是想在for的判断终止条件上置q.size()，但其实可以再赋初值的时候设置。
即(i=0;i<q.size();i++)和(i=q.size();i>0;i--)的区别。
*/
class Solution {
   public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            vector<int> tmp;
            for (int i = q.size(); i > 0; i--) {
                TreeNode* cur = q.front();
                q.pop();
                tmp.push_back(cur->val);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            res.push_back(tmp);
        }
        return res;
    }
};

/*
递归写法,要点在于每一层不一定要同时输入，可以分多步输入。因此设置row控制，通过row来记住此时的root应该输入到第几层。
*/
class Solution {
   public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        levelOrderChild(root, 0, res);
        return res;
    }

   private:
    void levelOrderChild(TreeNode* root, int row, vector<vector<int>>& res) {
        if (!root) return;
        if (res.size() == row) res.push_back({});
        res[row].push_back(root->val);
        levelOrderChild(root->left, row + 1, res);
        levelOrderChild(root->right, row + 1, res);
    }
};