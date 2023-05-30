#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Perform square root decomposition on an array
struct SqrtDecomposition {
    vector<int> arr;  // original array
    int blockSize;  // size of each block
    vector<int> blockSums;  // sum of elements in each block

    SqrtDecomposition(vector<int>& nums) {
        arr = nums;
        int n = arr.size();
        blockSize = sqrt(n);  // size of each block

        // Calculate the block sums
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            if ((i + 1) % blockSize == 0) {
                blockSums.push_back(sum);
                sum = 0;
            }
        }
        if (sum > 0) {
            blockSums.push_back(sum);
        }
    }

    // Update the value at a specific index
    void update(int index, int value) {
        int blockIndex = index / blockSize;
        arr[index] = value;

        // Recalculate the block sum
        int start = blockIndex * blockSize;
        int end = min((blockIndex + 1) * blockSize, int(arr.size()));
        blockSums[blockIndex] = 0;
        for (int i = start; i < end; i++) {
            blockSums[blockIndex] += arr[i];
        }
    }

    // Get the sum of elements in a given range
    int query(int left, int right) {
        int startBlock = left / blockSize;
        int endBlock = right / blockSize;
        int sum = 0;

        if (startBlock == endBlock) {
            // If the range is within a single block, iterate through the elements
            for (int i = left; i <= right; i++) {
                sum += arr[i];
            }
        } else {
            // If the range spans multiple blocks, calculate the sum of partial blocks
            for (int i = left; i < (startBlock + 1) * blockSize; i++) {
                sum += arr[i];
            }
            for (int i = startBlock + 1; i < endBlock; i++) {
                sum += blockSums[i];
            }
            for (int i = endBlock * blockSize; i <= right; i++) {
                sum += arr[i];
            }
        }

        return sum;
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 7, 9};

    SqrtDecomposition sd(nums);

    // Perform range queries
    cout << "Sum in range [1, 3]: " << sd.query(1, 3) << endl;
    cout << "Sum in range [2, 4]: " << sd.query(2, 4) << endl;

    // Update a value and perform range query again
    sd.update(2, 6);
    cout << "Sum in range [1, 3] after update: " << sd.query(1, 3) << endl;

    return 0;
}
