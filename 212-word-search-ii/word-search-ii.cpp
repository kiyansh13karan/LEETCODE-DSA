class Solution {
public:
    struct TrieNode {
        TrieNode* child[26];
        string word = "";
    };

    TrieNode* buildTrie(vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (string w : words) {
            TrieNode* node = root;
            for (char c : w) {
                int i = c - 'a';
                if (!node->child[i]) node->child[i] = new TrieNode();
                node = node->child[i];
            }
            node->word = w;
        }
        return root;
    }

    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* node, vector<string>& res) {
        char c = board[i][j];
        if (c == '#' || !node->child[c - 'a']) return;

        node = node->child[c - 'a'];

        if (node->word != "") {
            res.push_back(node->word);
            node->word = "";
        }

        board[i][j] = '#';

        int d[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (auto &x : d) {
            int ni = i + x[0], nj = j + x[1];
            if (ni>=0 && nj>=0 && ni<board.size() && nj<board[0].size())
                dfs(board, ni, nj, node, res);
        }

        board[i][j] = c;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = buildTrie(words);
        vector<string> res;

        for (int i=0;i<board.size();i++)
            for (int j=0;j<board[0].size();j++)
                dfs(board,i,j,root,res);

        return res;
    }
};