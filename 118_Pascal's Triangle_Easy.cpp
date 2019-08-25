/*
简单的递推就行了，第i行的元素a[j]由第i-1行的a[j-1]和a[j]得到。最后push1即新一行。
需要注意的是每行从后往前算可以减少中间量的使用。即在a[j]=a[j]+a[j-1]时。
*/
class Solution {
   public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        if (numRows <= 0)
            return res;
        vector<int> tmp = {1};
        res.push_back(tmp);
        while (numRows > 1) {
            for (int i = tmp.size() - 1; i > 0; i--)
                tmp[i] += tmp[i - 1];
            tmp.push_back(1);
            res.push_back(tmp);
            numRows--;
        }
        return res;
    }
};