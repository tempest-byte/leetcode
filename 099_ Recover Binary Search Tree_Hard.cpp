/*
leetcode自己都说O(n)复杂度是简单的。想了一会才想到BST有个很好的性质，就是中序遍历后是一个srot好的数组。所以只需要进行数组的排序，然后对所有节点进行赋值即可。
所以对此进行改进即可。既然是只有两个节点被互换，设其为b1,b2。
中序遍历后会出现[a1,a2,…,b1,ai,…,aj,b2,……]这种情况。其中，b1>ai,aj>b2。
所以只要根据b1，b2的左右大小比较即可。(注意特殊情况，b1,b2挨着。)
具体O(lgn)的空间复杂度，即树的高度。
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

/*
但是上述办法仍然不能达到O(1)空间复杂度。所以是利用某些节点的空子节点存储下一个遍历地址。具体思路和94题相同。
*/
class Solution {
   public:
    void recoverTree(TreeNode* root) {
        TreeNode* cur = root;          //当前节点
        TreeNode* next;                //提前运算，用以确定左子树是否遍历完毕
        TreeNode* pre = nullptr;       //中序遍历的前一节点
        int tmp = INT_MIN;             //前一节点的值。虽然可以用pre算出来，但是懒得步骤了
        TreeNode* fir = nullptr;       //存储错误的首节点
        TreeNode* sec = nullptr;       //错误的第二个节点
        while (cur) {
            if (cur->left) {           //cur->left的最右非空子节点即为中序遍历的cur前一节点，所以利用最右子节点的空子节点记录cur
                next = cur->left;
                while (next->right && next->right != cur) next = next->right;
                if (!next->right) {
                    next->right = cur;
                    cur = cur->left;
                } else {
                    if (tmp > cur->val) {
                        if (!fir) fir = pre;
                        sec = cur;
                    }
                    next->right = nullptr;
                    tmp = cur->val;
                    pre = cur;
                    cur = cur->right;
                }
            } else {
                if (tmp > cur->val) {
                    if (!fir) fir = pre;
                    sec = cur;
                }
                tmp = cur->val;
                pre = cur;
                cur = cur->right;
            }
        }
        fir->val = fir->val ^ sec->val;
        sec->val = fir->val ^ sec->val;
        fir->val = fir->val ^ sec->val;
    }
};