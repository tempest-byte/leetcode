/*
leetcode自己都说O(n)复杂度是简单的。想了一会才想到BST有个很好的性质，就是中序遍历后是一个srot好的数组。所以只需要进行数组的排序，然后对所有节点进行赋值即可。
所以对此进行改进即可。既然是只有两个节点被互换，设其为b1,b2。
中序遍历后会出现[a1,a2,…,b1,ai,…,aj,b2,……]这种情况。其中，b1>ai,aj>b2。
所以只要根据b1，b2的左右大小比较即可。(注意特殊情况，b1,b2挨着。)
*/
class Solution {
   public:
    void recoverTree(TreeNode* root) {
        InOrderRoot(root);
        int i = 0, j = 1;  //对应b1,b2紧挨的情况,此时res数组仅存在两个数
        if (res.size() == 4) j = 3;  //对应b1,b2中间存在其他数情况
        res[i]->val ^= res[j]->val;  //通过异或操作交换两个元素值
        res[j]->val ^= res[i]->val;
        res[i]->val ^= res[j]->val;
    }

   private:
    vector<TreeNode*> res;
    TreeNode* tmp;
    void InOrderRoot(TreeNode* root) {
        if (root->left) InOrderRoot(root->left);
        if (tmp && (tmp->val > root->val)) {
            res.push_back(tmp);
            res.push_back(root);
        }
        tmp = root;
        if (root->right) InOrderRoot(tmp->right);
    }
};