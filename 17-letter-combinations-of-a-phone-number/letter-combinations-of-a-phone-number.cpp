class Solution {
public:
    vector<string> ans;
    
    void solve(int idx, string digits, string curr, vector<string>& map){
        if(idx == digits.size()){
            ans.push_back(curr);
            return;
        }
        
        string letters = map[digits[idx] - '0'];
        
        for(char c : letters){
            solve(idx + 1, digits, curr + c, map);
        }
    }
    
    vector<string> letterCombinations(string digits) {
        if(digits == "") return {};
        
        vector<string> map = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        solve(0, digits, "", map);
        
        return ans;
    }
};