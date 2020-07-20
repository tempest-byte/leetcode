/*
第一眼就是递归哎。二分法从选最中间的元素作为根节点，小于放左，大于放右。
犹豫就会白给。
*/
class Solution {
   public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int len = nums.size();
        if (!len)
            return NULL;
        return helper(nums, 0, len - 1);
    }

   private:
    TreeNode* helper(vector<int>& nums, int start, int end) {
        if (start > end)
            return NULL;
        else {
            TreeNode* cur = new TreeNode(nums[(start + end) / 2]);
            cur->left = helper(nums, start, (start + end) / 2 - 1);
            cur->right = helper(nums, (start + end) / 2 + 1, end);
            return cur;
        }
    }
};