class Trie {
public:
    
    struct Node {
        Node* links[26];
        bool end = false;
    };
    
    Node* root;

    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node* node = root;
        for(char c : word){
            int i = c - 'a';
            if(!node->links[i])
                node->links[i] = new Node();
            node = node->links[i];
        }
        node->end = true;
    }
    
    bool search(string word) {
        Node* node = root;
        for(char c : word){
            int i = c - 'a';
            if(!node->links[i])
                return false;
            node = node->links[i];
        }
        return node->end;
    }
    
    bool startsWith(string prefix) {
        Node* node = root;
        for(char c : prefix){
            int i = c - 'a';
            if(!node->links[i])
                return false;
            node = node->links[i];
        }
        return true;
    }
};