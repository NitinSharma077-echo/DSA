#include <bits/stdc++.h>
using namespace std;
struct Stack {
    vector<int> data;
    int top;

    MyStack() : top(-1) {}

    void push(int x) {
        data.push_back(x);
        top++;
    }

    void pop() {
        if (!isEmpty()) {
            data.pop_back();
            top--;
        }
    }

    int peek() {
        if (!isEmpty())
            return data[top];
        return -1;
    }

    bool isEmpty() {
        return top < 0;
    }
};


class Solution {
public:
// Largest Rectangle in Histogram
    int largestRectangleArea(vector<int>& heights) {
        stack<int> s;
        heights.push_back(0);  // Sentinel to flush the stack
        int area = 0;

        for (int i = 0; i < heights.size(); i++) {
            while (!s.empty() && heights[i] < heights[s.top()]) {
                int h = heights[s.top()];
                s.pop();
                int width = s.empty() ? i : i - s.top() - 1;
                area = max(area, h * width);
            }
            s.push(i);
        }
        return area;
    }
//     
};