/*
螺旋递归。想法真的强。真的没想出来还可以这么做。
https://blog.csdn.net/linhuanmars/article/details/23236995
维护两个数组，global和local。
其中global[i][j]为前j天进行i次买卖交易的最大值，local[i][j]也为前j天进行i次购买的最大值，但最后一次（第i次）的出售必须在第j天。
可得g[i][j]=max(g[i][j-1],l[i][j])
    l[i][j]=max(g[i-1][j]+max(prices[j]-prices[j-1],0),l[i][j-1]+(prices[j]-prices[j-1]))
global的推导很简单，即最后一次出售分在不在第j天两种情况。
local推导分为两部分，最后一次交易的买入是否在第j-1天：
    一、如果在第j-1天，则与之前的i-1次交易只要在前j-1天完成即可。
    二、如果买入不在第j天，则只需要利用local[i][j-1]，将最后一次交易的卖出时间更新即可。
*/
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty())
            return 0;
        int n = prices.size();
        vector<int> global(n, 0);
        vector<int> local(n, 0);
        for (int i = 0; i < 2; i++) {
            int tmp = 0;
            for (int j = 1; j < n; j++) {
                int diff = prices[j] - prices[j - 1];
                local[j] = max(tmp + max(diff, 0), local[j - 1] + diff);
                tmp = global[j];
                global[j] = max(global[j - 1], local[j]);
            }
        }
        return global[n - 1];
    }
};

/*
以下是我自己写的，2O(n)的复杂度，空间上只用了几个变量。但是代码量太大，而且不好扩充。
首先理清思路，只能赚两次差价，则肯定不会出现买、卖在同一天。
之后单次交易最高差价肯定要保留。记买在第i天，卖在第j天。第二次交易有两种情况：
1、第二次与第一次无关（买卖均发生在第i天前或第j天后）。
2、第二次交易在第一次交易之中（买卖均发生在i,j天内，而且要先卖后买）。
第二种情况相当于从prices[i+1:j—1]中逆序找到交易的最大值。
*/
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len < 2)
            return 0;
        // tmp_min,tmp_max负责记录当前区间的买卖日期。pri_min,pri_max记录全局最优交易买卖日期。
        int tmp_min = 0, tmp_max = 0, pri_min, pri_max;
        // val_min=prices[tmp_min],val_max=prices[tmp_max]
        int val_min = prices[0], val_max = prices[0];
        // vector[0]记录最右交易值，vector[1]记录次优交易。
        vector<int> res(2, 0);
        // for循环为了找到交易最大值的买卖日期。
        for (int i = 1; i < len; i++) {
            val_min = prices[tmp_min];
            val_max = prices[tmp_max];
            if (prices[i] > val_max)
                tmp_max = i;
            if (prices[i] < val_min || i == len - 1) {
                if (i == len - 1)
                    val_max = prices[tmp_max];
                if (val_min != val_max) {
                    if (val_max - val_min > res[0]) {
                        pri_min = tmp_min;
                        pri_max = tmp_max;
                        res[1] = res[0];
                        res[0] = val_max - val_min;
                    } else
                        res[1] = max(res[1], val_max - val_min);
                }
                tmp_min = tmp_max = i;
            }
        }
        //对应prices={1，7，2，3}这种情况。需要把2，3放进去
        if (pri_max < len - 2) {
            val_min = val_max = prices[pri_max + 1];
            for (int i = pri_max + 1; i < len; i++) {
                if (prices[i] > val_max)
                    val_max = prices[i];
                else if (prices[i] < val_min) {
                    if (val_min != val_max)
                        res[1] = max(res[1], val_max - val_min);
                    val_min = val_max = prices[i];
                }
            }
            res[1] = max(res[1], val_max - val_min);
        }
        //对应注释中的第二种情况。
        if (res[0] == res[1] || pri_max - pri_min < 3)
            return res[0] + res[1];
        val_min = val_max = prices[pri_max - 1];
        for (int i = pri_max - 1; i > pri_min; i--) {
            if (prices[i] > val_max)
                val_max = prices[i];
            else if (prices[i] < val_min) {
                if (val_min != val_max)
                    res[1] = max(res[1], val_max - val_min);
                val_min = val_max = prices[i];
            }
        }
        res[1] = max(res[1], val_max - val_min);
        return res[0] + res[1];
    }
};