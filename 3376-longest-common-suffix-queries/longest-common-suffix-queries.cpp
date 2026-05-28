class Solution {
public:

    struct Node {
        int child[26];
        int idx;

        Node() {
            memset(child, -1, sizeof(child));
            idx = -1;
        }
    };

    vector<Node> trie;
    vector<string> words;

    Solution() {
        trie.push_back(Node());
    }

    bool better(int a, int b) {

        if (b == -1)
            return true;

        if (words[a].size() < words[b].size())
            return true;

        if (words[a].size() == words[b].size() && a < b)
            return true;

        return false;
    }

    void insert(string s, int index) {

        reverse(s.begin(), s.end());

        int node = 0;

        if (better(index, trie[node].idx))
            trie[node].idx = index;

        for (char c : s) {

            int x = c - 'a';

            if (trie[node].child[x] == -1) {
                trie[node].child[x] = trie.size();
                trie.push_back(Node());
            }

            node = trie[node].child[x];

            if (better(index, trie[node].idx))
                trie[node].idx = index;
        }
    }

    int search(string s) {

        reverse(s.begin(), s.end());

        int node = 0;

        for (char c : s) {

            int x = c - 'a';

            if (trie[node].child[x] == -1)
                break;

            node = trie[node].child[x];
        }

        return trie[node].idx;
    }

    vector<int> stringIndices(vector<string>& wordsContainer,
                              vector<string>& wordsQuery) {

        words = wordsContainer;

        for (int i = 0; i < wordsContainer.size(); i++) {
            insert(wordsContainer[i], i);
        }

        vector<int> ans;

        for (auto &q : wordsQuery) {
            ans.push_back(search(q));
        }

        return ans;
    }
};