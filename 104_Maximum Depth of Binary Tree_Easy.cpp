/*
直接队列，没什么好讲的。
*/
class Solution {
   public:
    int maxDepth(TreeNode* root) {
        int res = 0;
        if (!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            for (int i = q.size(); i > 0; i--) {
                TreeNode* cur = q.front();
                q.pop();
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            res++;
        }
        return res;
    }
};
/* 
递归看起来简单，但会更花时间。感觉主要花在了max上面。
*/
  class Solution {
  public:
	  int maxDepth(TreeNode* root) {
		  if (!root)return 0;
		  return 1 + max(maxDepth(root->left), maxDepth(root->right));
	  }
  };