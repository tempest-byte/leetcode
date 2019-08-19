/*
自己想到的就是递归。的确动态规划的办法没想出来。
递归就比较简单了，没什么好说的。
*/
class Solution {
   public:
    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size())
            return false;
        return sb_topic(s1, s2);
    }

   private:
    bool sb_topic(string s1, string s2) {
        if (s1 == s2)
            return true;
        int num = s1.size();
        vector<int> nums(26, 0);
        for (int i = num - 1; i >= 0; i--) {
            nums[s1[i] - 'a']++;
            nums[s2[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (nums[i] != 0)
                return false;
        }
        for (int j = 1; j < num; j++) {
            if ((sb_topic(s1.substr(0, j), s2.substr(num - j)) &&
                 sb_topic(s1.substr(j), s2.substr(0, num - j))) ||
                (sb_topic(s1.substr(0, j), s2.substr(0, j)) &&
                 sb_topic(s1.substr(j), s2.substr(j)))) {
                return true;
            }
        }
        return false;
    }
};

/*
之前一直想用二维动态规划去做，结果发现做不出来，就转而使用hash_map做。
就是把运算过的两个字符串的bool值存到unorder_map中，但是很浪费时间。放弃。
动态规划参照网上方案，三重规划。
https://blog.csdn.net/linhuanmars/article/details/24506703
*/
class Solution {
   public:
    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size())
            return false;
        if (s1 == s2)
            return true;
        int n = s1.size();
        vector<vector<vector<bool> > > dp(
            n, vector<vector<bool> >(n, vector<bool>(n + 1, false)));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i][j][1] = s1[i] == s2[j];
            }
        }
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                for (int j = 0; j <= n - len; ++j) {
                    for (int k = 1; k < len; ++k) {
                        if ((dp[i][j][k] && dp[i + k][j + k][len - k]) ||
                            (dp[i + k][j][len - k] && dp[i][j + len - k][k])) {
                            dp[i][j][len] = true;
                        }
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};