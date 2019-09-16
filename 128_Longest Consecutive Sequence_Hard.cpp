//简练太多，思路相同，对于每个元素查找其左右是否存在，注意要将查找过的键值删除，避免重复操作。
class Solution {
   public:
    int longestConsecutive(vector<int>& nums) {
        int res = 0;
        unordered_set<int> s(nums.begin(), nums.end());
        for (int val : nums) {
            if (!s.count(val))
                continue;
            s.erase(val);
            int pre = val - 1, next = val + 1;
            while (s.count(pre))
                s.erase(pre--);
            while (s.count(next))
                s.erase(next++);
            res = max(res, next - pre - 1);
        }
        return res;
    }
};

//对于每个新元素连接后，只需要更新新边界的值即可。所以可以在边界记录之前的数组长度。
class Solution {
   public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty())
            return 0;
        int res = 1;
        unordered_map<int, int> num_map;
        for (auto num : nums) {
            if (num_map.count(num))
                continue;
            else {
                int left = num_map.count(num - 1) ? num_map[num - 1] : 0;
                int right = num_map.count(num + 1) ? num_map[num + 1] : 0;
                int sum = left + right + 1;
                num_map[num] = sum;
                num_map[num - left] = sum;
                num_map[num + right] = sum;
                res = max(res, sum);
            }
        }
        return res;
    }
};