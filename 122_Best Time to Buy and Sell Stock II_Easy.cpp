/*
题目真的不好，思考的是股票今天卖出去了就不能今天再买。谁知道它想说的是同一天可以又卖又买？？？
我都想用DP做了。。而且想的巨恶心。
*/
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len < 1)
            return 0;
        int res = 0, pri_min = prices[0], pri_max = pri_min;
        for (int i = 1; i < len; i++) {
            if (pri_max > prices[i]) {
                if (pri_min < pri_max)
                    res = res + pri_max - pri_min;
                pri_min = prices[i];
                pri_max = prices[i];
            }
            if (pri_max < prices[i])
                pri_max = prices[i];
        }
        return (res + pri_max - pri_min);
    }
};
//嗯，根据121别人的思路自己写的。
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int res = 0, pre = INT_MAX;
        for (int price : prices) {
            res += max(0, price - pre);
            pre = price;
        }
        return res;
    }
};