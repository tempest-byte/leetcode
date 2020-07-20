//注意可以利用取余简化判断。而且计算机中-3%5=-3
class Solution {
   public:
    bool isPalindrome(string s) {
        int len = s.size();
        if (len < 2)
            return true;
        int start = 0, end = len - 1;
        while (start < end) {
            if (!isValidChar(s[start]))
                start++;
            else if (!isValidChar(s[end]))
                end--;
            else if ((s[start] + 32 - 'a') % 32 != (s[end] + 32 - 'a') % 32)
                return false;
            else {
                start++;
                end--;
            }
        }
        return true;
    }

   private:
    bool isValidChar(char a) {
        if (a >= '0' && a <= '9')
            return true;
        if (a >= 'a' && a <= 'z')
            return true;
        if (a >= 'A' && a <= 'Z')
            return true;
        return false;
    }
};