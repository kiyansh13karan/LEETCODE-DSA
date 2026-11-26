class Solution {
public:
    bool canAliceWin(int n) {
        int turn = 10;

        while (n >= turn) {
            n -= turn;
            turn--;
        }

        return turn % 2 == 1;
    }
};