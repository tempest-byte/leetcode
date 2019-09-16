/*
首先找到到当前指针的前m的数的最小值min_m,以及下一个比min_m小的数min_n。
则在(m,n)之间，找到当前区域的best choice。
之后从min_n开始重复上述操作。
*/
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len <= 0)
            return 0;
        int pri_min = prices[0], pri_max = prices[0], res = 0;

        for (int i = 1; i < len; i++) {
            if (prices[i] < pri_min) {
                if (pri_min < pri_max)
                    res = max(res, pri_max - pri_min);
                pri_min = prices[i];
                pri_max = pri_min;
            } else if (prices[i] > pri_max)
                pri_max = prices[i];
        }

        return max(res, pri_max - pri_min);
    }
};
//比自己想的简洁N倍，总是想控制长度加上限制条件，但写的贼复杂。
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int res = 0, buy = INT_MAX;
        for (int price : prices) {
            buy = min(buy, price);
            res = max(res, price - buy);
        }
        return res;
    }
};