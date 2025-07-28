#include <bits/stdc++.h>
using namespace std;

// Swap helper function
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Bubble Sort
vector<int> bubblesort(vector<int> arr) {
    int n = arr.size();
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(arr[i] > arr[j])
                swap(arr[i], arr[j]);
    return arr;
}

// Selection Sort
vector<int> selectionsort(vector<int> arr) {
    int n = arr.size();
    for(int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for(int j = i + 1; j < n; j++)
            if(arr[j] < arr[minIndex])
                minIndex = j;
        swap(arr[i], arr[minIndex]);
    }
    return arr;
}

// Insertion Sort
vector<int> insertionsort(vector<int> arr) {
    int n = arr.size();
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return arr;
}

// Quick Sort
int partition(vector<int>& arr, int low, int high){
    int pivot=arr[high];
    int i=low-1;
    for(int j=low;j<high;j++){
        if(arr[j]<pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
} 
vector<int> quicksort(vector<int> arr,int low,int high) {
    if(arr.size() <= 1) return arr;
    int p=partition(arr, 0, arr.size() - 1);
    quicksort(arr,0 ,p-1);
    quicksort(arr, p + 1, arr.size() - 1);
    return arr;
}
//shell sort
vector<int> shellsort(vector<int> arr){
    int n = arr.size();
    for(int gap=n/2;gap>0;gap/=2){
        for(int i=gap;i<n;i++){
            int temp=arr[i];
            int j=i;
            for(j=i;j>=gap && arr[j-gap]>temp;j-gap){
                arr[j] = arr[j - gap];
                arr[j] = temp;
            }
        }
        return arr;
    }
}
//bucket sort
vector<int> bucketSort(vector<float> arr,int n) {
    vector<float> bucket[n];
    for(int i=0;i<n;i++){
        int index=n*arr[i];
        bucket[index].push_back(arr[i]);
    }
    for(int i=0;i<n;i++){
        sort(bucket[i].begin(), bucket[i].end());
    }
    vector<float> sortedArray;
    for(int i=0;i<n;i++){
        for(int j=0;j<bucket[i].size();j++){
            sortedArray.push_back(bucket[i][j]);
        }
    }
    return sortedArray;
}
// Print array
void printArray(const vector<float>& arr) {
    for(float val : arr) cout << val << " ";
    cout << endl;
}

// Main function
int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    vector<int> sorted;

    cout << "Original Array: ";
    printArray(arr);

    cout << "\nChoose sorting algorithm:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Insertion Sort\n";
    cout << "4. Quick Sort\n";
    cout << "5. Shell Sort\n";
    cout << "6. Bucket Sort\n";
    cout << "Enter choice (1-6): ";

    int choice;
    cin >> choice;

    switch(choice) {
        case 1: sorted = bubblesort(arr); break;
        case 2: sorted = selectionsort(arr); break;
        case 3: sorted = insertionsort(arr); break;
        case 4: sorted = quicksort(arr,0,arr.size()-1); break;
        case 5: sorted = shellsort(arr); break;
        case 6: {
            vector<float> floatArr(arr.begin(), arr.end());
            vector<float> sortedFloat = bucketSort(floatArr, arr.size());
            sorted.assign(sortedFloat.begin(), sortedFloat.end());
            break;
        }
        default: cout << "Invalid choice\n"; return 1;
    }

    cout << "Sorted Array: ";
    printArray(sorted);

    return 0;
}
