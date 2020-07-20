/*
最常规的办法，动态规划。
记tmp[i][j]代表s1的前i个单词，s2的前j个单词，如果能符合s3的前i+j个单词，则tmp[i][j]=1，否则为0。
则tmp[i][j]可以由tmp[i-1][j]和tmp[i][j-1]递归得到，分别对应s3的第i+j个单词是来自于s1还是s2。（注意考虑到边界0问题所以需要在for循环中先讨论一下）
*/
class Solution {
   public:
    bool isInterleave(string s1, string s2, string s3) {
        int num_1 = s1.size(), num_2 = s2.size(), num_3 = s3.size();
        if (num_1 + num_2 != num_3) return false;
        vector<vector<bool>> tmp(num_1 + 1, vector<bool>(num_2 + 1, false));
        for (int i = 0; i < num_1 + 1; i++) {
            for (int j = 0; j < num_2 + 1; j++) {
                if (i == 0) {
                    if (j == 0)
                        tmp[i][j] = true;
                    else
                        tmp[i][j] = (tmp[i][j - 1] && s2[j - 1] == s3[j - 1]);
                } else if (j == 0)
                    tmp[i][j] = (tmp[i - 1][j] && s1[i - 1] == s3[i - 1]);
                else
                    tmp[i][j] = (tmp[i][j - 1] && s2[j - 1] == s3[i + j - 1]) ||
                                (tmp[i - 1][j] && s1[i - 1] == s3[i + j - 1]);
            }
        }
        return tmp[num_1][num_2];
    }
};

/*
下面两种解法都是根据大佬而来，https://www.cnblogs.com/grandyang/p/4298664.html。相较而言还是感觉DP比较简单。
假如我们不想用DP的二维数组，还可以怎么保存数据呢？具体其实可以用堆栈存取k=m成功的(i,j)。然后重新更新k=m+1的(i,j)。
*/
class Solution {
   public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size()) return false;
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size(), k = 0;
        unordered_set<int> s;
        queue<int> q{{0}};
        while (!q.empty() && k < n3) {
            int len = q.size();
            for (int t = 0; t < len; ++t) {
                int i = q.front() / n3, j = q.front() % n3;
                q.pop();
                if (i < n1 && s1[i] == s3[k]) {
                    int key = (i + 1) * n3 + j;
                    if (!s.count(key)) {
                        s.insert(key);
                        q.push(key);
                    }
                }
                if (j < n2 && s2[j] == s3[k]) {
                    int key = i * n3 + j + 1;
                    if (!s.count(key)) {
                        s.insert(key);
                        q.push(key);
                    }
                }
            }
            ++k;
        }
        return !q.empty() && k == n3;
    }
};

/*
递归解法。DFS。主要是从后往前，记录的是错误的值。其实仔细思考一下和dp区别不大。
*/
class Solution {
   public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size()) return false;
        unordered_set<int> s;
        return helper(s1, 0, s2, 0, s3, 0, s);
    }
    bool helper(string& s1, int i, string& s2, int j, string& s3, int k,
                unordered_set<int>& s) {
        int key = i * s3.size() + j;
        if (s.count(key)) return false;
        if (i == s1.size()) return s2.substr(j) == s3.substr(k);
        if (j == s2.size()) return s1.substr(i) == s3.substr(k);
        if ((s1[i] == s3[k] && helper(s1, i + 1, s2, j, s3, k + 1, s)) ||
            (s2[j] == s3[k] && helper(s1, i, s2, j + 1, s3, k + 1, s)))
            return true;
        s.insert(key);
        return false;
    }
};
