class Solution {
public:
    string convert(string s, int numRows) {

        if (numRows == 1 || numRows >= s.size())
            return s;

        vector<string> rows(numRows);

        int curRow = 0;
        bool down = true;

        for (char ch : s) {

            rows[curRow] += ch;

            if (curRow == 0)
                down = true;
            else if (curRow == numRows - 1)
                down = false;

            if (down)
                curRow++;
            else
                curRow--;
        }

        string ans;

        for (string row : rows)
            ans += row;

        return ans;
    }
};