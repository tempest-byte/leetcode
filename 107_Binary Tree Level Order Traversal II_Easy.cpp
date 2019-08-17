/*
队列写法，每次得到的队列只需要放在上一层父节点之前。
但是注意到vector中push_back为O(1)时间复杂度，insert为O(n)复杂度，所以还是推荐用push_back。
做法就是正常从root节点开始做，最后得到的数组reverse一下。
*/
class Solution {
   public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if (!root)
            return res;
        queue<TreeNode*> qu;
        qu.push(root);
        while (!qu.empty()) {
            vector<int> tmp;
            for (int i = qu.size(); i > 0; i--) {
                TreeNode* cur = qu.front();
                qu.pop();
                tmp.push_back(cur->val);
                if (cur->left)
                    qu.push(cur->left);
                if (cur->right)
                    qu.push(cur->right);
            }
            res.insert(res.begin(), tmp);
        }
        return res;
    }
};

/*
递归函数做法。首先计算每层的到叶子节点的最大高度，然后再用递归去做。浪费时间不写了。
下面连接的第二种解法就是递归。
https://leetcode.com/problems/binary-tree-level-order-traversal-ii/discuss/35108/C%2B%2B-4ms-solution!
*/