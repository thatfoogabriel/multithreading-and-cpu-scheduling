#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <sstream>

using namespace std;

mutex mtx;

// Perform merge operation
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create left and right half arrays
    vector<int> L(n1), R(n2);

    // Copy to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge temporary arrays
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main merge sort function
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Sort first half
void sortFirstHalf(vector<int>& arr, int start, int end) {
    mergeSort(arr, start, end);
}

// Sort second half
void sortSecondHalf(vector<int>& arr, int start, int end) {
    mergeSort(arr, start, end);
}

// Merge two sorted halves
void mergeHalves(vector<int>& arr, int start, int mid, int end) {
    merge(arr, start, mid, end);
}

int main() {
    // Prompt user for array
    cout << "Enter some numbers separated by spaces: ";
    string input;
    getline(cin, input);

    // Parse user input
    istringstream iss(input);
    vector<int> arr;
    int num;

    // Build user's array
    while (iss >> num) {
        arr.push_back(num);
    }

    int n = arr.size();

    // Create 2 threads to sort halves
    thread t1(sortFirstHalf, ref(arr), 0, (n / 2) - 1);
    thread t2(sortSecondHalf, ref(arr), n / 2, n - 1);

    // Join threads
    t1.join();
    t2.join();

    // Merge sorted halves
    mergeHalves(arr, 0, (n / 2) - 1, n - 1);

    // Print sorted array
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
