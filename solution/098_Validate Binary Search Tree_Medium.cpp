/*
最简单的办法，递归。每个节点的取值范围其实都是根据父节点计算得来的。
设父节点范围[m,n]，父节点值为k。则左子节点取值范围为[m,k),右子节点取值范围为(k,n]。
如果想要减少边界检查，可以使用long。但是32位系统和64位中对long的长度定义不同，保险起见可以用longlong。
至于此题还可以使用中序遍历进行操作。中序遍历输出的应该为有序数组。
*/
class Solution {
   public:
    bool isValidBST(TreeNode* root) {
        return isValidChild(root, INT_MIN, INT_MAX);
    }

   private:
    bool isValidChild(TreeNode* root, int num_min, int num_max) {
        if (!root) return true;
        int num = root->val;
        if (num < num_min || num > num_max) return false;
        if (num == INT_MIN)
            return !root->left && isValidChild(root->right, num + 1, num_max);
        else if (num == INT_MAX)
            return !root->right && isValidChild(root->left, num_min, num - 1);
        else
            return isValidChild(root->left, num_min, num - 1) &&
                   isValidChild(root->right, num + 1, num_max);
    }
};