#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to update the Binary Indexed Tree for minimum values
void updateMinBIT(vector<int>& BIT, int index, int value) {
    while (index < BIT.size()) {
        BIT[index] = min(BIT[index], value);
        index += index & (-index);
    }
}

// Function to perform a range update in the Binary Indexed Tree for minimum values
void rangeUpdateMinBIT(vector<int>& BIT, int left, int right, int value) {
    updateMinBIT(BIT, left, value);
    updateMinBIT(BIT, right + 1, INT_MAX); // Set a maximum sentinel value
}

// Function to get the minimum value up to a given index from the Binary Indexed Tree
int getPrefixMin(vector<int>& BIT, int index) {
    int minVal = INT_MAX;
    while (index > 0) {
        minVal = min(minVal, BIT[index]);
        index -= index & (-index);
    }
    return minVal;
}

// Function to get the minimum value in a given range from the Binary Indexed Tree
int rangeQueryMinBIT(vector<int>& BIT, int left, int right) {
    return getPrefixMin(BIT, right) - getPrefixMin(BIT, left - 1);
}


int main() {
    // Example usage
    vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int n = arr.size();

    // Create Binary Indexed Tree (BIT) with an extra element
    vector<int> minBIT(n + 1, INT_MAX);

    // Perform a range update for minimum values
    rangeUpdateMinBIT(minBIT, 2, 8, 2);
  
    // Perform a range query for minimum values
    int minVal = rangeQueryMinBIT(minBIT, 4, 6);
    cout << "Minimum value in range [4, 6]: " << minVal << endl;

    return 0;
}
