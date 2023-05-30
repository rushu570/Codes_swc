#include <iostream>
#include <vector>

using namespace std;

// Function to update the Binary Indexed Tree
void updateBIT(vector<int>& BIT, int index, int value) {
    while (index < BIT.size()) {
        BIT[index] += value;
        index += index & (-index);
    }
}

// Function to perform a range update in the Binary Indexed Tree
void rangeUpdateBIT(vector<int>& BIT, int left, int right, int value) {
    updateBIT(BIT, left, value);
    updateBIT(BIT, right + 1, -value);
}

// Function to get the prefix sum up to a given index from the Binary Indexed Tree
int getPrefixSum(vector<int>& BIT, int index) {
    int sum = 0;
    while (index > 0) {
        sum += BIT[index];
        index -= index & (-index);
    }
    return sum;
}

// Function to get the sum in a given range from the Binary Indexed Tree
int rangeQueryBIT(vector<int>& BIT, int left, int right) {
    return getPrefixSum(BIT, right) - getPrefixSum(BIT, left - 1);
}

int main() {
    // Example usage
    vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int n = arr.size();

    // Create Binary Indexed Tree (BIT) with an extra element
    vector<int> BIT(n + 1, 0);

    // Perform a range update
    rangeUpdateBIT(BIT, 2, 8, 2);

    // Perform a range query
    int sum = rangeQueryBIT(BIT, 4, 6);
    cout << "Sum in range [4, 6]: " << sum << endl;

    return 0;
}
