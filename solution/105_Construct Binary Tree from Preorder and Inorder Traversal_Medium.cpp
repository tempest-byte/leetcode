/*
使用stack来做，这样可以不用递归来节省空间。两个指针pre_pi和in_pi分别指向前序遍历和中序遍历。
如preorder[7,1,2,3,4,5,…]和inorder[7,5,…,4,…,]可知1的左子节点是2，2的左子节点是3，……，4的左子节点是5。inorder中5和4之间的节点为5的右子树。
因此有如下操作。
cur即为当前需要操作节点，操作为：补充其右子树的部分节点，这些节点满足为左父子关系，且最后一个节点无左子节点。
如上文7节点之后无左子树，所以对其右子树进行补充，首先7右子节点为1，然后1~5建立左父子关系。其中1~4顺序进栈。
此时cur在5处，之后如果inorder5和4紧挨，说明5没有右子树。所以cur退至4，4节点出栈。
*/
class Solution {
   public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode* pre = new TreeNode(0);  //建立额外节点，以便统一while情况。
        int pre_pi = 0, in_pi = 0, len = preorder.size(), tmp;
        TreeNode* cur = pre;
        stack<TreeNode*> st;  //根据前序遍历保存节点。
        //每次循环都保证只构造一条左父子关系或去冗余操作。根据cur节点先构造右子节点，然后构造右子节点的所有左子节点。
        while (in_pi < len) {
            //去冗余，对应cur=5,st.top=4,inorder[in_pi]=4的情况，说明5没有右子树。
            if (!st.empty() && inorder[in_pi] == st.top()->val) {
                cur = st.top();  // cur变为stack中上一节点
                st.pop();
                in_pi++;
            } else {  //构造左父子关系，第一个节点比较特殊，它是cur的右子节点，其他节点均为上一节点的左子节点。
                TreeNode* RightChild = new TreeNode(preorder[pre_pi]);
                cur->right = RightChild;
                cur = RightChild;
                pre_pi++;
                //判断此次构造的左父子关系是否仅有单元素
                if (preorder[pre_pi - 1] != inorder[in_pi]) {
                    tmp = inorder[in_pi];
                    st.push(cur);
                    do {
                        TreeNode* LeftChild = new TreeNode(preorder[pre_pi]);
                        cur->left = LeftChild;
                        cur = LeftChild;
                        pre_pi++;
                        st.push(cur);
                    } while (preorder[pre_pi - 1] != tmp);
                    st.pop();
                }
                in_pi++;  //当前中序遍历的节点已加入，所以指针+1
            }
        }
        return pre->right;
    }
};

/*
此外也有递归做法。
举例 preorder={1，2，3，4，5，6，7，8，9，10}
inorder={5，4，3，6，2，1，8，10，9，7}
注意到1为根节点，则根据中序遍历可知，{5，4，3，6，2}（1之前的数）为其左子树，后面的为其右子树。
而且在前序遍历中也可以看到，1的后续5个数即为其左子树。其他为右子树。
所以根据当前节点在inorder中的出现位置，确定左右子树的数目，划分之后将其转到前序遍历中，可立即得到左右子节点分别是2，7。
据此递归即可。
*/
