class Solution {
public:
    int totalNQueens(int n) {
        vector<int> col(n,0), diag1(2*n,0), diag2(2*n,0);
        return backtrack(0,n,col,diag1,diag2);
    }

    int backtrack(int row,int n,vector<int>& col,vector<int>& d1,vector<int>& d2){
        if(row==n) return 1;

        int count=0;
        for(int c=0;c<n;c++){
            if(col[c] || d1[row+c] || d2[row-c+n]) continue;

            col[c]=d1[row+c]=d2[row-c+n]=1;
            count += backtrack(row+1,n,col,d1,d2);
            col[c]=d1[row+c]=d2[row-c+n]=0;
        }

        return count;
    }
};