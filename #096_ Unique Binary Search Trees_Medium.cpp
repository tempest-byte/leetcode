/*
emmm，感觉这道题没什么意思。做上一题的时候就顺手写完了。。。
不过其中引用到卡塔兰数，维基百科https://zh.wikipedia.org/wiki/%E5%8D%A1%E5%A1%94%E5%85%B0%E6%95%B0
*/
class Solution {
   public:
    int numTrees(int n) {
        if (n == 0) return 0;
        vector<int> res = {1};
        for (int i = 1; i <= n; i++) {
            int tmp = 0;
            for (int j = 0; j < i; j++) tmp += res[j] * res[i - j - 1];
            res.push_back(tmp);
        }
        return res[n];
    }
};
/*
卡塔兰数的数学推导:
An = C(2n,n) / (n+1)
1、构造生成函数g(x),并推导出g(x)x的函数解析式。
2、利用泰勒展开，爆算。。。
详情请见https://blog.csdn.net/u011452172/article/details/78219457
*/
class Solution {
   public:
    int numTrees(int n) {
        long res = 1;
        for (int i = n + 1; i <= 2 * n; ++i) res = res * i / (i - n);
        return res / (n + 1);
    }
};