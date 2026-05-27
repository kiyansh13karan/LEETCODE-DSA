class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<int> first(128, -1);
        vector<int> last(128, -1);

        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];

            if (first[ch] == -1)
                first[ch] = i;

            last[ch] = i;
        }

        int ans = 0;

        for (char c = 'a'; c <= 'z'; c++) {
            char upper = c - 'a' + 'A';

            if (last[c] != -1 &&
                first[upper] != -1 &&
                last[c] < first[upper]) {
                ans++;
            }
        }

        return ans;
    }
};