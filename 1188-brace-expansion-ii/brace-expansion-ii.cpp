#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        int index = 0;
        set<string> result = parseExpression(expression, index);
        return vector<string>(result.begin(), result.end());
    }

private:
    set<string> parseExpression(const string& s, int& i) {
        set<string> currentSet;
        set<string> currentProduct = {""};

        while (i < s.length() && s[i] != '}') {
            if (s[i] == ',') {
                currentSet.insert(currentProduct.begin(), currentProduct.end());
                currentProduct = {""};
                i++;
            } else if (s[i] == '{') {
                i++;
                set<string> subSet = parseExpression(s, i);
                i++;
                currentProduct = product(currentProduct, subSet);
            } else {
                string word = "";
                while (i < s.length() && islower(s[i])) {
                    word += s[i];
                    i++;
                }
                currentProduct = product(currentProduct, {word});
            }
        }

        currentSet.insert(currentProduct.begin(), currentProduct.end());
        return currentSet;
    }

    set<string> product(const set<string>& set1, const set<string>& set2) {
        set<string> res;
        for (const string& a : set1) {
            for (const string& b : set2) {
                res.insert(a + b);
            }
        }
        return res;
    }
};