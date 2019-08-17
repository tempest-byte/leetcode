/*
上题基础上递归，偶数行顺序输入。奇数行每次插在最前面，做到逆序输入。当然也可以按照这个思路实现队列的做法。具体见https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/discuss/33825/c++-5ms-version:-one-queue-and-without-reverse-operation-by-using-size-of-each-level
*/
class Solution {
   public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        levelOrderChild(root, 0, res);
        return res;
    }

   private:
    void levelOrderChild(TreeNode* root, int row, vector<vector<int>>& res) {
        if (!root) return;
        if (res.size() == row) res.push_back({});
        if (row % 2 == 0)  //判断此行奇偶
            res[row].push_back(root->val);
        else
            res[row].insert(res[row].begin(), root->val);
        levelOrderChild(root->left, row + 1, res);
        levelOrderChild(root->right, row + 1, res);
    }
};
/*
使用两个栈来操作。有点像倒豆子，来回倒的过程中就会后进的先出。
s1为顺序，s2为逆序。所以s1输入到s2的时候left先输入，由于栈的特性就会left后输出。达到s2中的逆序要求。
*/
class Solution {
   public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        stack<TreeNode*> s1, s2;
        s1.push(root);
        while (!s1.empty() || !s2.empty()) {
            vector<int> tmp;
            TreeNode* cur;
            if (s1.empty()) {
                for (int i = s2.size(); i > 0; i--) {
                    cur = s2.top();
                    s2.pop();
                    tmp.push_back(cur->val);
                    if (cur->right) s1.push(cur->right);
                    if (cur->left) s1.push(cur->left);
                }
            } else {
                for (int i = s1.size(); i > 0; i--) {
                    cur = s1.top();
                    s1.pop();
                    tmp.push_back(cur->val);
                    if (cur->left) s2.push(cur->left);
                    if (cur->right) s2.push(cur->right);
                }
            }
            res.push_back(tmp);
        }
        return res;
    }
};