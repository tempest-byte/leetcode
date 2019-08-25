/*
这种问题妥妥的动态规划啊。二维虽然很好写但是很浪费空间和时间，所以需要将其转化为一维数组。
原设计tmp[i][j]代表s[0:i)和t[0:j)满足的情况数。（设计tmp.size(s_len+1,t_len+1)是为了统一边界情况）
注意到tmp[i][j]=tmp[i-1][j-1]+tmp[i-1][j]（对应s[i-1]==t[i-1])或者tmp[i][j]=tmp[i-1][j](对应s[i-1]!=t[j-1]),每一行仅和上一行有关系，所以只需要用单行去做即可。
*/
class Solution {
   public:
    int numDistinct(string s, string t) {
        int s_len = s.size(), t_len = t.size();
        vector<long long> tmp(t_len + 1, 0);
        tmp[0] = 1;
        for (int i = 1; i <= s_len; i++) {
            for (int j = t_len; j >= 1; j--) {
                //从后往前，这样就不需要无关变量存储值。
                if (s[i - 1] == t[j - 1])
                    tmp[j] = tmp[j - 1] + tmp[j];
                else
                    tmp[j] = tmp[j];
            }
        }
        return tmp[t_len];
    }
};
