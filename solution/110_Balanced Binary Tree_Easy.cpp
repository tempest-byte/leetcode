/*
最简单的办法，递归。对于每个节点，通过叶子节点得知本节点左右树的高度。判断是否超出限制。
我是使用的FLAG res来表示子树是不是满足题意，其实完全可以在判断不对的情况下return -1。因为高度不可能为负数。
*/
class Solution {
   public:
    bool isBalanced(TreeNode* root) {
        bool res = true;
        TreeDepth(root, res);
        return res;
    }

   private:
    int TreeDepth(TreeNode* root, bool& res) {
        if (!root)
            return 0;
        int LeftDepth = TreeDepth(root->left, res);
        if (!res)
            return 0;
        int RightDepth = TreeDepth(root->right, res);
        if (!res)
            return 0;
        if (abs(LeftDepth - RightDepth) > 1)
            res = false;
        return max(LeftDepth, RightDepth) + 1;
    }
};