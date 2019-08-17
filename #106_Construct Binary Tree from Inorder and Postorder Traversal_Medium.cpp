/*
最简单的办法，递归咯
postoder分组的最后一个就是根节点，据此去inorder查找就可以了。
*/
class Solution {
   public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return bT(inorder, 0, inorder.size() - 1, postorder, 0,
                  postorder.size() - 1);
    }

   private:
    TreeNode* bT(vector<int>& inorder,
                 int i_start,
                 int i_end,
                 vector<int>& postorder,
                 int p_start,
                 int p_end) {
        if (i_start > i_end)
            return NULL;
        int i = i_start;
        for (; i <= i_end; i++) {
            if (inorder[i] == postorder[p_end])
                break;
        }
        TreeNode* cur = new TreeNode(inorder[i]);
        cur->left = bT(inorder, i_start, i - 1, postorder, p_start,
                       p_start + i - 1 - i_start);
        cur->right = bT(inorder, i + 1, i_end, postorder, p_start + i - i_start,
                        p_end - 1);
        return cur;
    }
};

/*
很有意思的一点，一个二叉树的后续遍历倒过来看是其镜像二叉树的先序遍历。
而二叉树的中序遍历倒过来还是镜像二叉树的中序遍历。
所以可以把两个数组倒过来，然后就是105题了，得到本题的镜像二叉树。
思路很有意思，代码就是拼凑了一下之前的代码和使用了镜像二叉树。
*/
class Solution {
   public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        vector<int> in_var, post_var;
        for (int i = inorder.size() - 1; i >= 0; i--) {
            in_var.push_back(inorder[i]);
            post_var.push_back(postorder[i]);
        }
        TreeNode* res = buildTree1(post_var, in_var);
        return invertTree(res);
    }

    TreeNode* buildTree1(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> m;
        for (int i = 0; i < inorder.size(); i++)
            m[inorder[i]] = i;
        return helper(preorder, 0, preorder.size() - 1, inorder, 0,
                      inorder.size() - 1, m);
    }

    TreeNode* helper(vector<int>& preorder,
                     int pStart,
                     int pEnd,
                     vector<int>& inorder,
                     int iStart,
                     int iEnd,
                     unordered_map<int, int>& m) {
        if (pStart > pEnd)
            return NULL;
        TreeNode* root = new TreeNode(preorder[pStart]);
        int i = m[preorder[pStart]];
        root->left = helper(preorder, pStart + 1, pStart + i - iStart, inorder,
                            iStart, i - 1, m);
        root->right = helper(preorder, pStart + i - iStart + 1, pEnd, inorder,
                             i + 1, iEnd, m);
        return root;
    }
    TreeNode* invertTree(TreeNode* root) {
        if (!root)
            return NULL;
        TreeNode* tmp = root->left;
        root->left = invertTree(root->right);
        root->right = invertTree(tmp);
        return root;
    }
};

/*
这就很有意思了，如果不用镜像二叉树，只用两个倒序数组，就会发现和105题的栈方法很相似。
和105很像，区别在于所有left，right互换，数组倒着读入。
*/
class Solution {
   public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        TreeNode* pre = new TreeNode(0);
        int post_pi = postorder.size() - 1, in_pi = post_pi, tmp;
        TreeNode* cur = pre;
        stack<TreeNode*> st;
        while (in_pi >= 0) {
            if (!st.empty() && inorder[in_pi] == st.top()->val) {
                cur = st.top();
                st.pop();
                in_pi--;
            } else {
                TreeNode* LeftChild = new TreeNode(postorder[post_pi]);
                cur->left = LeftChild;
                cur = LeftChild;
                post_pi--;
                if (postorder[post_pi + 1] != inorder[in_pi]) {
                    tmp = inorder[in_pi];
                    st.push(cur);
                    do {
                        TreeNode* RightChild = new TreeNode(postorder[post_pi]);
                        cur->right = RightChild;
                        cur = RightChild;
                        post_pi--;
                        st.push(cur);
                    } while (postorder[post_pi + 1] != tmp);
                    st.pop();
                }
                in_pi--;
            }
        }
        return pre->left;
    }
};