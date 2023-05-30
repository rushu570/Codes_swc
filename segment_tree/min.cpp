#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Segment Tree for Range Minimum Queries
struct SegmentTree {
    vector<int> tree;  // segment tree
    int n;  // size of the input array

    SegmentTree(vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);  // initialize the segment tree with appropriate size
        build(nums, 0, 0, n - 1);  // build the segment tree
    }

    void build(vector<int>& nums, int idx, int left, int right) {
        if (left == right) {
            tree[idx] = nums[left];  // leaf node, store the element
            return;
        }

        int mid = left + (right - left) / 2;
        build(nums, 2 * idx + 1, left, mid);  // build left subtree
        build(nums, 2 * idx + 2, mid + 1, right);  // build right subtree

        // combine the results of left and right subtree
        tree[idx] = min(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    int query(int idx, int left, int right, int qleft, int qright) {
        if (left > qright || right < qleft) {
            return numeric_limits<int>::max();  // no overlap, return infinity
        }
        if (left >= qleft && right <= qright) {
            return tree[idx];  // complete overlap, return the value
        }

        int mid = left + (right - left) / 2;
        int leftMin = query(2 * idx + 1, left, mid, qleft, qright);  // query left subtree
        int rightMin = query(2 * idx + 2, mid + 1, right, qleft, qright);  // query right subtree

        // combine the results of left and right subtree
        return min(leftMin, rightMin);
    }

    void update(int idx, int left, int right, int pos, int newVal) {
        if (left == right) {
            tree[idx] = newVal;  // leaf node, update the value
            return;
        }

        int mid = left + (right - left) / 2;
        if (pos <= mid) {
            update(2 * idx + 1, left, mid, pos, newVal);  // update left subtree
        } else {
            update(2 * idx + 2, mid + 1, right, pos, newVal);  // update right subtree
        }

        // combine the results of left and right subtree
        tree[idx] = min(tree[2 * idx + 1], tree[2 * idx + 2]);
    }
};

int main() {
    vector<int> nums = {5, 3, 7, 2, 8};

    SegmentTree st(nums);

    // Perform range minimum queries
    cout << "Minimum in range [1, 3]: " << st.query(0, 0, st.n - 1, 1, 3) << endl;
    cout << "Minimum in range [2, 4]: " << st.query(0, 0, st.n - 1, 2, 4) << endl;

    // Update an element and perform range minimum query
    st.update(0, 0, st.n -
