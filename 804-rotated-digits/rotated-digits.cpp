class Solution {
public:
    int rotatedDigits(int n) {
        int count = 0;
        
        for(int i = 1; i <= n; i++) {
            int num = i;
            bool valid = true, changed = false;
            
            while(num > 0) {
                int d = num % 10;
                
                if(d == 3 || d == 4 || d == 7) {
                    valid = false;
                    break;
                }
                if(d == 2 || d == 5 || d == 6 || d == 9) {
                    changed = true;
                }
                
                num /= 10;
            }
            
            if(valid && changed) count++;
        }
        
        return count;
    }
};