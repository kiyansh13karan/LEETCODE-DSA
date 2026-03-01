class TrieNode {
public:
    TrieNode* child[26];
    bool end;

    TrieNode() {
        end = false;
        for(int i=0;i<26;i++) child[i] = NULL;
    }
};

class WordDictionary {
public:
    TrieNode* root;

    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* node = root;
        for(char c : word){
            int idx = c - 'a';
            if(!node->child[idx])
                node->child[idx] = new TrieNode();
            node = node->child[idx];
        }
        node->end = true;
    }

    bool dfs(string &word, int i, TrieNode* node){
        if(i == word.size()) return node->end;

        if(word[i] == '.'){
            for(int j=0;j<26;j++){
                if(node->child[j] && dfs(word,i+1,node->child[j]))
                    return true;
            }
            return false;
        }

        int idx = word[i]-'a';
        if(!node->child[idx]) return false;

        return dfs(word,i+1,node->child[idx]);
    }

    bool search(string word) {
        return dfs(word,0,root);
    }
};