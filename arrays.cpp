#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Regular Expression Matching
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[0][0] = true;
       
        for (int j = 1; j <= n; ++j) {
            if (p[j-1] == '*') {
                dp[0][j] = dp[0][j-2]; 
            }
        }
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j-1] == '.' || p[j-1] == s[i-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else if (p[j-1] == '*') {
                    dp[i][j] = dp[i][j-2];
                    if (p[j-2] == '.' || p[j-2] == s[i-1]) {
                        dp[i][j] = dp[i][j] || dp[i-1][j];
                    }
                }
            }
        }
        
        return dp[m][n];
    }

    // Find index of first occur string in the strings
    int str(string s, string p) {
        int n = s.size();
        int m = p.size();
        for (int i = 0; i <= n - m; i++) {
            int j = 0;
            while (j < m && s[i + j] == p[j]) {
                j++;
            }
            if (j == m) {
                return i;
            }
        }
        return -1;
    }

    // Next permutation
    vector<vector<int>> per(vector<int>& nums) {
        vector<vector<int>> result;
        result.push_back(nums);
        int n = nums.size();
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }
        if (i >= 0) {
            int j = n - 1;
            while (j >= 0 && nums[j] <= nums[i]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());
        result.push_back(nums);
        return result;
    }

    vector<vector<int>> nextper(vector<int>& nums) {
        vector<vector<int>> result;
        result.push_back(nums);
        int n = nums.size();
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }
        if (i >= 0) {
            int j = n - 1;
            while (j >= 0 && nums[j] <= nums[i]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());

        result.push_back(nums);
        return result;
    }

    // Longest valid parentheses
    int lvp(string s) {
        int left = 0, right = 0, leng = 0;
        for (char c : s) {
            if (c == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                leng = max(leng, left + right);
            } else if (right > left) {
                left = right = 0;
            }
        }
        left = right = 0;
        reverse(s.begin(), s.end());
        for (char c : s) {
            if (c == ')') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                leng = max(leng, left + right);
            } else if (right > left) {
                left = right = 0;
            }
        }
        return leng;
    }

    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0) return -1;
        int i = 0;
        while (i < n) {
            if (nums[i] == target) {
                return i;
            }
            i++;
        }
        return -1;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> ans(2, -1);
        int start = 0, end = n - 1;
        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] < target) {
                start = mid + 1;
            } else if (nums[mid] > target) {
                end = mid - 1;
            } else {
                ans[0] = mid;
                end = mid - 1;
            }
        }
        start = 0;
        end = n - 1;
        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target) {
                ans[1] = mid;
                start = mid + 1;
            } else if (nums[mid] < target) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        return ans;
    }

    int searchInsert(vector<int>& nums, int target) {
        int i = 0;
        int n = nums.size();
        while (i < n) {
            if (nums[i] == target) {
                return i;
            } else if (target < nums[i]) {
                return i;
            }
            i++;
        }
        return i;
    }

    // Valid Sudoku
    bool isvalid(vector<vector<char>>& board) {
        vector<vector<bool>> rows(9, vector<bool>(9, false));
        vector<vector<bool>> cols(9, vector<bool>(9, false));
        vector<vector<bool>> box(9, vector<bool>(9, false));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                int num = board[i][j] - '1';
                int boxIndex = (i / 3) * 3 + (j / 3);
                if (rows[i][num] || cols[j][num] || box[boxIndex][num]) {
                    return false;
                }
                rows[i][num] = true;
                cols[j][num] = true;
                box[boxIndex][num] = true;
            }
        }
        return true;
    }

    // Count and Say
    string countsay(int n) {
        if (n == 1) return "1";
        string prev = countsay(n - 1);
        string result = "";
        int count = 1;
        for (int i = 1; i < prev.size(); i++) {
            if (prev[i] == prev[i - 1]) {
                count++;
            } else {
                result += to_string(count) + prev[i - 1];
                count = 1;
            }
        }
        result += to_string(count) + prev.back();
        return result;
    }

    vector<int> range(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0) return {};
        vector<int> ans(2, -1);
        int i = 0, j = n - 1;
        while (i <= j) {
            int mid = i + (j - i) / 2;
            if (nums[mid] == target) {
                ans[0] = mid;
                j = mid - 1;
            } else if (nums[mid] < target) {
                i = mid + 1;
            } else {
                j = mid - 1;
            }
        }
        i = 0;
        j = n - 1;
        while (i <= j) {
            int mid = i + (j - i) / 2;
            if (nums[mid] == target) {
                ans[1] = mid;
                i = mid + 1;
            } else if (nums[mid] < target) {
                i = mid + 1;
            } else {
                j = mid - 1;
            }
        }
        return ans;
    }

    vector<vector<int>> ans;
    vector<int> curr;
    vector<int> numsCopy;

    void back(int i, int remain) {
        if (remain == 0) {
            ans.push_back(curr);
            return;
        }
        if (remain < 0 || i >= numsCopy.size()) {
            return;
        }
        curr.push_back(numsCopy[i]);
        back(i + 1, remain - numsCopy[i]);
        curr.pop_back();
        back(i + 1, remain);
    }

    vector<vector<int>> combine(vector<int>& nums, int target) {
        if (nums.empty()) return {};
        sort(nums.begin(), nums.end());
        numsCopy = nums;
        ans.clear();
        curr.clear();
        back(0, target);
        return ans;
    }

    // First Missing Positive
    int missing(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int small = 1;
        for (int num : arr) {
            if (num == small) {
                small++;
            }
        }
        return small;
    }

    // Trapping rain water
    int trap(vector<int>& height) {
        int n = height.size();
        int left = 0, right = n - 1, water = 0, maxleft = 0, maxright = 0;
        while (left < right) {
            maxleft = max(maxleft, height[left]);
            maxright = max(maxright, height[right]);
            if (maxleft < maxright) {
                water += maxleft - height[left];
                left++;
            } else {
                water += maxright - height[right];
                right--;
            }
        }
        return water;
    }

    // Multiply strings
    string multiply(string s, string p) {
        int m = s.size(), n = p.size();
        if (m == 0 || n == 0) return "0";
        vector<int> result(m + n, 0);
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int mul = (s[i] - '0') * (p[j] - '0');
                int sum = mul + result[i + j + 1];
                result[i + j] += sum / 10;
                result[i + j + 1] = sum % 10;
            }
        }
        string res = "";
        for (int num : result) {
            if (!(res.empty() && num == 0)) {
                res += to_string(num);
            }
        }
        return res.empty() ? "0" : res;
    }
};

int main() {
    Solution sol;
    return 0;
}
