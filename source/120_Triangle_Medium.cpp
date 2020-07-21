/*
本来想用自顶向下的非递归写法，结果发现想法错了。
思路：从底向上，tmp的前k个值对应自底连接到第k层的每个节点的最小值。
    之后推导k-1层的时候，只需要将tmp的相邻节点取min，然后加上本节点的数字即可。
*/
class Solution {
   public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int len = triangle.size();
        vector<int> tmp = triangle.back();
        for (int i = len - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++)
                tmp[j] = min(tmp[j], tmp[j + 1]) + triangle[i][j];
        }
        return tmp[0];
    }
};

/*
如果上式看明白了，那自顶向下也就不难了。不过因为首尾节点和中间节点不同，统一情况很尴尬。
如果想写也是可以写的。
*/
