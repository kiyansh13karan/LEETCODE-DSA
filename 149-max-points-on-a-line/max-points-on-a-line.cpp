class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if(n <= 2) return n;
        
        int ans = 0;
        
        for(int i = 0; i < n; i++){
            map<pair<int,int>, int> mp;
            int dup = 1;
            
            for(int j = i+1; j < n; j++){
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                
                if(dx==0 && dy==0){
                    dup++;
                    continue;
                }
                
                int g = __gcd(dx, dy);
                dx/=g; dy/=g;
                
                mp[{dx,dy}]++;
                ans = max(ans, mp[{dx,dy}] + dup);
            }
            ans = max(ans, dup);
        }
        return ans;
    }
};