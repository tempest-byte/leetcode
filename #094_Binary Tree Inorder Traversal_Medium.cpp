/*递归，不再啰嗦。本解法主要利用stack。
进栈为特殊操作：每次放入节点，必须将其所有左子节点放入。
从栈取出节点，先打印本身，然后将右子节点进行进栈操作。
*/
class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		if (root == NULL)return res;
		stack<TreeNode*> tmp;
		TreeNode* cur =root;
		while (cur != NULL) {//进栈操作：将所有左子节点统一进栈
			tmp.push(cur);
			cur = cur->left;
		}
		while (!tmp.empty()) {
			res.push_back(tmp.top()->val);
			cur = tmp.top();
			tmp.pop();
			cur = cur->right;
			while (cur != NULL) {//与上文标注的进栈操作相同。
				tmp.push(cur);
				cur = cur->left;
			}
		}
		return res;
	}
}; 

/*
Morris Traversal详情请去 https://www.cnblogs.com/grandyang/p/4297300.html
解决的事情是遍历完某右子节点的寻找下一个打印节点问题。递归中利用内存中未执行完的父进程，栈中利用top节点即下一个节点。
主要思路为将当前节点的左子节点为起点，查找其最右子节点。然后将其右子节点设置为当前节点，即形成环路。
因此在实际操作中主要分为两步。
第一步：将当前节点与其左子节点的最右子节点连接，形成环路。
第二步：对于每个节点，先检查是否生成环路，如果有第一步的环，说明其左子树已经打印完毕，否则要先打印左子树。
 */
class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		if (!root)return res;
		TreeNode *cur = root;
		TreeNode* pre;
		while (cur) {
			if (!cur->left) {
				res.push_back(cur->val);
				cur = cur->right;
			}
			else {
				pre = cur->left;
				while (pre->right && pre->right != cur)pre = pre->right;
				if (!pre->right) {//第一次操作cur。此时还未成环。需要将最右子节点与cur连接。
					pre->right = cur;
					cur = cur->left;
				}
				else {//第二次操作cur，此时发现有环。所以可以进行打印本身和右子树。
					res.push_back(cur->val);
					pre->right = NULL;
					cur = cur->right;
				}
			}
		}
		return res;
	}
};