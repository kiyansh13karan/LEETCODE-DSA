class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        set<int> st;

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                st.insert(grid[i][j]); // size 0

                for(int k=1;i+2*k<m && j-k>=0 && j+k<n;k++){
                    int sum=0, x=i, y=j;

                    for(int t=0;t<k;t++) sum+=grid[x+t][y-t];
                    for(int t=0;t<k;t++) sum+=grid[x+k+t][y-k+t];
                    for(int t=0;t<k;t++) sum+=grid[x+2*k-t][y+t];
                    for(int t=0;t<k;t++) sum+=grid[x+k-t][y+k-t];

                    st.insert(sum);
                }
            }
        }

        vector<int> res;
        for(auto it=st.rbegin(); it!=st.rend() && res.size()<3; it++)
            res.push_back(*it);

        return res;
    }
};