/*
想到的就是递归。
常见的一个技巧就是使用。先把当前节点放入。不论成功与否其子树结束后都将此节点取出。
*/
class Solution {
   public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (!root)
            return {};
        vector<int> tmp;
        vector<vector<int>> res;
        RecursivePath(root, sum, tmp, res);
        return res;
    }

   private:
    void RecursivePath(TreeNode* root,
                       int sum,
                       vector<int>& tmp,
                       vector<vector<int>>& res) {
        sum -= root->val;
        tmp.push_back(root->val);
        if (sum == 0 && !root->left && !root->right)
            res.push_back(tmp);
        else {
            if (root->left)
                RecursivePath(root->left, sum, tmp, res);
            if (root->right)
                RecursivePath(root->right, sum, tmp, res);
        }
        tmp.pop_back();
    }
};

/*
不好意思，虽然能写出来，但和大佬的总结程度还是差距太大。虽然能分情况讨论，但是很难总结。
https://www.cnblogs.com/grandyang/p/4042156.html
*/
class Solution {
   public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<TreeNode*> tmp;
        TreeNode *cur = root, *pre = NULL;
        while (cur || !tmp.empty()) {
            while (cur) {
                tmp.push_back(cur);
                sum -= cur->val;
                cur = cur->left;
            }
            cur = tmp.back();
            if (!cur->right && !cur->left) {
                if (sum == 0) {
                    vector<int> ret;
                    for (auto i : tmp)
                        ret.push_back(i->val);
                    res.push_back(ret);
                }
            }
            if (cur->right && cur->right != pre)
                cur = cur->right;
            else {
                pre = cur;
                sum += cur->val;
                cur = NULL;
                tmp.pop_back();
            }
        }
        return res;
    }
};