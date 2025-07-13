#include <bits/stdc++.h>
using namespace std;

class Search {
public:
    int linearsearch(const vector<int>& arr, int key) {
        for(int i = 0; i < arr.size(); i++) {
            if(arr[i] == key) {
                return i; 
            }
        }
        return -1; 
    }

    int binarysearch(const vector<int>& arr, int key) {
        int left = 0;
        int right = arr.size() - 1;
        if(arr.empty()) return -1;

        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(arr[mid] == key) {
                return mid;
            } else if(arr[mid] < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
};
int main() {
    Search search;
    vector<int> arr = {1, 2, 3, 4, 5};
    int key = 3;

    int linearResult = search.linearsearch(arr, key);
    cout << "Linear Search Result: " << linearResult << endl;

    int binaryResult = search.binarysearch(arr, key);
    cout << "Binary Search Result: " << binaryResult << endl;

    return 0;
}