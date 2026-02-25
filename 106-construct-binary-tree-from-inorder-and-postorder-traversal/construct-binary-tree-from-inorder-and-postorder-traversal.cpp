/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int,int> mp;
        
        for(int i=0;i<inorder.size();i++)
            mp[inorder[i]] = i;
        
        int postIndex = postorder.size()-1;
        
        return solve(inorder, postorder, postIndex, 0, inorder.size()-1, mp);
    }
    
    TreeNode* solve(vector<int>& inorder, vector<int>& postorder,
                    int &postIndex, int left, int right,
                    unordered_map<int,int>& mp){
        
        if(left > right) return NULL;
        
        int rootVal = postorder[postIndex--];
        TreeNode* root = new TreeNode(rootVal);
        
        int index = mp[rootVal];
        
        root->right = solve(inorder, postorder, postIndex, index+1, right, mp);
        root->left = solve(inorder, postorder, postIndex, left, index-1, mp);
        
        return root;
    }
};