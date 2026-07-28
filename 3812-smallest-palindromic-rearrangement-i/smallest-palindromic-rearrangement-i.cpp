class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> cnt(26, 0);

        for (char ch : s)
            cnt[ch - 'a']++;

        string firstHalf = "";
        char middle = '\0';

        for (int i = 0; i < 26; i++) {
            firstHalf.append(cnt[i] / 2, char('a' + i));

            if (cnt[i] % 2 == 1)
                middle = char('a' + i);
        }

        string secondHalf = firstHalf;
        reverse(secondHalf.begin(), secondHalf.end());

        if (middle != '\0')
            return firstHalf + middle + secondHalf;

        return firstHalf + secondHalf;
    }
};