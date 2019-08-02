/*
BST:对于每一个节点，左子树的值均小于它，右子树的值均大于它.
按道理不算难，但恶心的地方在于递归的返回值上。因为对于每个数字的new数目不同，所以只能把左右子节点列表返回。相当浪费时间
其中tmp主要是避免重复操作，对于区间为(i,j)的root节点可以进行复用（注意到此时（i，j）结构固定所以能够复用）
思路很简单，对于每个数字，都根据左右节点数乘积的值为基数，进行new操作。然后连接左右子节点即可。
*/
class Solution {
   public:
    vector<TreeNode *> generateTrees(int n) {
        if (n <= 0) return {};
        vector<vector<vector<TreeNode *>>> tmp(n,
                                               vector<vector<TreeNode *>>(n));
        return insert_num(1, n, tmp);
    }

   private:
    vector<TreeNode *> insert_num(int n_min, int n_max,
                                  vector<vector<vector<TreeNode *>>> &tmp) {
        if (n_min > n_max) return {NULL};
        if (!tmp[n_min - 1][n_max - 1].empty())
            return tmp[n_min - 1][n_max - 1];
        vector<TreeNode *> res;
        for (int i = n_min; i <= n_max; i++) {
            auto left = insert_num(n_min, i - 1, tmp),
                 right = insert_num(i + 1, n_max, tmp);
            for (auto node_left : left) {
                for (auto node_right : right) {
                    TreeNode *pre = new TreeNode(i);
                    pre->left = node_left;
                    pre->right = node_right;
                    res.push_back(pre);
                }
            }
        }
        tmp[n_min - 1][n_max - 1] = res;
        return res;
    }
};