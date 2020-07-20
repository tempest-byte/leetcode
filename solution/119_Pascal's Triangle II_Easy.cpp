//118题的中间过程，不再叙述。
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int>tmp = { 1 };
		  while (rowIndex > 0) {
			  for (int i = tmp.size()-1; i > 0; i--) {
				  tmp[i] += tmp[i-1];
			  }
			  tmp.push_back(1);
              rowIndex--;
		  }
        return tmp;
    }
};

//当然也可以直接使用排列组合去做。不过注意到乘积可能超过int，所以用double
class Solution {
public:
    vector<int> getRow(int n) {
        vector<int> result = {1};
        for (double i = 1; i <= n; ++i)
            result.push_back(result.back() * (n - i + 1) / i);
        return result;
    }
};