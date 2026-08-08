class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> last(m, -1);

        // Find positions from right where word2 suffix
        // can be matched exactly.
        int i = n - 1;
        int j = m - 1;

        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
            i--;
        }

        vector<int> ans;
        bool changed = false;

        j = 0;

        for (i = 0; i < n && j < m; i++) {

            // Exact match
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            }

            // Use our one allowed mismatch
            else if (!changed &&
                     (j == m - 1 || i < last[j + 1])) {
                
                ans.push_back(i);
                j++;
                changed = true;
            }
        }

        // Could not form word2
        if (j != m)
            return {};

        return ans;
    }
};