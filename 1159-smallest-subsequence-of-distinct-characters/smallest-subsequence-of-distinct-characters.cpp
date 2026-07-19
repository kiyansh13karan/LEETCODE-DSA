class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> last(26);
        vector<bool> used(26, false);

        for (int i = 0; i < s.size(); i++)
            last[s[i] - 'a'] = i;

        string st;

        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];

            if (used[ch - 'a'])
                continue;

            while (!st.empty() &&
                   st.back() > ch &&
                   last[st.back() - 'a'] > i) {

                used[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(ch);
            used[ch - 'a'] = true;
        }

        return st;
    }
};