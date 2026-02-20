class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        
        vector<pair<int,int>> dirs = {
            {-1,-1},{-1,0},{-1,1},
            {0,-1},       {0,1},
            {1,-1},{1,0},{1,1}
        };
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int live = 0;
                
                for(auto d : dirs) {
                    int ni = i + d.first;
                    int nj = j + d.second;
                    
                    if(ni>=0 && ni<m && nj>=0 && nj<n && 
                       abs(board[ni][nj]) == 1)
                        live++;
                }
                
                if(board[i][j] == 1 && (live < 2 || live > 3))
                    board[i][j] = -1;   // live → dead
                if(board[i][j] == 0 && live == 3)
                    board[i][j] = 2;    // dead → live
            }
        }
        
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                board[i][j] = board[i][j] > 0 ? 1 : 0;
    }
};