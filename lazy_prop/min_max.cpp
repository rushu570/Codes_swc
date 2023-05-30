#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Segment Tree with Lazy Propagation for Range Minimum and Maximum Queries
struct SegmentTree {
    vector<int> treeMin;  // segment tree for minimum values
    vector<int> treeMax;  // segment tree for maximum values
    vector<int> lazy;  // lazy propagation array
    int n;  // size of the input array

    SegmentTree(vector<int>& nums) {
        n = nums.size();
        treeMin.resize(4 * n);  // initialize the segment tree for minimum values with appropriate size
        treeMax.resize(4 * n);  // initialize the segment tree for maximum values with appropriate size
        lazy.resize(4 * n);  // initialize the lazy propagation array with appropriate size
        build(nums, 0, 0, n - 1);  // build the segment tree
    }

    void build(vector<int>& nums, int idx, int left, int right) {
        if (left == right) {
            treeMin[idx] = nums[left];  // leaf node, store the element
            treeMax[idx] = nums[left];  // leaf node, store the element
            return;
        }

        int mid = left + (right - left) / 2;
        build(nums, 2 * idx + 1, left, mid);  // build left subtree
        build(nums, 2 * idx + 2, mid + 1, right);  // build right subtree

        // combine the results of left and right subtree for minimum values
        treeMin[idx] = min(treeMin[2 * idx + 1], treeMin[2 * idx + 2]);

        // combine the results of left and right subtree for maximum values
        treeMax[idx] = max(treeMax[2 * idx + 1], treeMax[2 * idx + 2]);
    }

    void propagate(int idx, int left, int right) {
        if (lazy[idx] != 0) {
            treeMin[idx] += lazy[idx];  // update the node value for minimum values
            treeMax[idx] += lazy[idx];  // update the node value for maximum values

            if (left != right) {
                lazy[2 * idx + 1] += lazy[idx];  // update left child's lazy value
                lazy[2 * idx + 2] += lazy[idx];  // update right child's lazy value
            }

            lazy[idx] = 0;  // clear the current node's lazy value
        }
    }

    int queryMin(int idx, int left, int right, int qleft, int qright) {
        propagate(idx, left, right);  // propagate the lazy value

        if (left > qright || right < qleft) {
            return numeric_limits<int>::max();  // no overlap, return maximum value
        }
        if (left >= qleft && right <= qright) {
            return treeMin[idx];  // complete overlap, return the minimum value
        }

        int mid = left + (right - left) / 2;
        int leftMin = queryMin(2 * idx + 1, left, mid, qleft, qright);  // query left subtree
        int rightMin = queryMin(2 * idx + 2, mid + 1, right, qleft, qright);  // query right subtree

        // combine the results of left and right subtree for minimum values
        return min(leftMin, rightMin);
    }

    int queryMax(int idx, int left, int right, int qleft, int qright) {
        propagate(idx, left, right);  // propagate the lazy value

        if (left > qright || right < qleft) {
            return numeric_limits<int>::min();  // no overlap, return minimum value
        }
        if (left >= qleft && right <= qright) {
            return treeMax[idx];  // complete overlap, return the maximum value
        }

        int mid = left + (right - left) / 2;
        int leftMax = queryMax(2 * idx + 1, left, mid, qleft, qright);  // query left subtree
        int rightMax = queryMax(2 * idx + 2, mid + 1, right, qleft, qright);  // query right subtree

        // combine the results of left and right subtree for maximum values
        return max(leftMax, rightMax);
    }

    void update(int idx, int left, int right, int qleft, int qright, int delta) {
        propagate(idx, left, right);  // propagate the lazy value

        if (left > qright || right < qleft) {
            return;  // no overlap, do nothing
        }
        if (left >= qleft && right <= qright) {
            treeMin[idx] += delta;  // update the node value for minimum values
            treeMax[idx] += delta;  // update the node value for maximum values

            if (left != right) {
                lazy[2 * idx + 1] += delta;  // update left child's lazy value
                lazy[2 * idx + 2] += delta;  // update right child's lazy value
            }

            return;
        }

        int mid = left + (right - left) / 2;
        update(2 * idx + 1, left, mid, qleft, qright, delta);  // update left subtree
        update(2 * idx + 2, mid + 1, right, qleft, qright, delta);  // update right subtree

        // combine the results of left and right subtree for minimum values
        treeMin[idx] = min(treeMin[2 * idx + 1], treeMin[2 * idx + 2]);

        // combine the results of left and right subtree for maximum values
        treeMax[idx] = max(treeMax[2 * idx + 1], treeMax[2 * idx + 2]);
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 7, 9};

    SegmentTree st(nums);

    // Perform range minimum and maximum queries
    cout << "Minimum in range [1, 3]: " << st.queryMin(0, 0, st.n - 1, 1, 3) << endl;
    cout << "Maximum in range [2, 4]: " << st.queryMax(0, 0, st.n - 1, 2, 4) << endl;

    // Update a range and perform range minimum and maximum queries
    st.update(0, 0, st.n - 1, 1, 3, 2);
    cout << "Minimum in range [1, 3] after update: " << st.queryMin(0, 0, st.n - 1, 1, 3) << endl;
    cout << "Maximum in range [1, 3] after update: " << st.queryMax(0, 0, st.n - 1, 1, 3) << endl;

    return 0;
}
