class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> ans;
        string digits = "123456789";

        int minLen = to_string(low).length();
        int maxLen = to_string(high).length();

        for (int len = minLen; len <= maxLen; len++) {
            for (int start = 0; start + len <= 9; start++) {
                int num = stoi(digits.substr(start, len));
                if (num >= low && num <= high) {
                    ans.push_back(num);
                }
            }
        }

        return ans;
    }
};