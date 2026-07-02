class Solution {
public:
    bool canFinish(vector<int>& piles, int h, int speed) {
        long long hours = 0;

        for (int bananas : piles) {
            hours += (bananas + speed - 1) / speed; // ceil division
        }

        return hours <= h;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = *max_element(piles.begin(), piles.end());

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (canFinish(piles, h, mid))
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};