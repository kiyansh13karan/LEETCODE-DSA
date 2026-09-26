class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key-value pairs
        for (auto &p : knowledge) {
            mp[p[0]] = p[1];
        }

        string ans;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(') {
                string key;

                i++; // move after '('

                while (s[i] != ')') {
                    key += s[i];
                    i++;
                }

                // Check if key exists
                if (mp.count(key))
                    ans += mp[key];
                else
                    ans += "?";
            }
            else {
                ans += s[i];
            }
        }

        return ans;
    }
};