#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int height(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        int area = 0;
        int i = 0, j = n - 1;
        while(i < j) {
            int h = min(nums[i], nums[j]);
            int width = j - i;
            area = max(area, h * width);
            if(nums[i] < nums[j]) {
                i++;
            } else {
                j--;
            }
        }
        return area; 
    }
};

int main() {
    Solution sol;
    vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Maximum area: " << sol.height(heights) << endl;
    return 0;
}
