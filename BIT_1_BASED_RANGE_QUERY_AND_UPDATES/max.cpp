#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to update the Binary Indexed Tree for maximum values
void updateMaxBIT(vector<int>& BIT, int index, int value) {
    while (index < BIT.size()) {
        BIT[index] = max(BIT[index], value);
        index += index & (-index);
    }
}

// Function to perform a range update in the Binary Indexed Tree for maximum values
void rangeUpdateMaxBIT(vector<int>& BIT, int left, int right, int value) {
    updateMaxBIT(BIT, left, value);
    updateMaxBIT(BIT, right + 1, INT_MIN); // Set a minimum sentinel value
}

// Function to get the maximum value up to a given index from the Binary Indexed Tree
int getPrefixMax(vector<int>& BIT, int index) {
    int maxVal = INT_MIN;
    while (index > 0) {
        maxVal = max(maxVal, BIT[index]);
        index -= index & (-index);
    }
    return maxVal;
}

// Function to get the maximum value in a given range from the Binary Indexed Tree
int rangeQueryMaxBIT(vector<int>& BIT, int left, int right) {
    return getPrefixMax(BIT, right) - getPrefixMax(BIT, left - 1);
}

int main() {
    // Example usage
    vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int n = arr.size();

    // Create Binary Indexed Tree (BIT) with an extra element
    vector<int> maxBIT(n + 1, INT_MIN);

    // Perform a range update for maximum values
    rangeUpdateMaxBIT(maxBIT, 2, 8, 5);
  
    int maxVal = rangeQueryMaxBIT(maxBIT, 4, 6);
    cout << "Maximum value in range [4, 6]: " << maxVal << endl;

    return 0;
}

