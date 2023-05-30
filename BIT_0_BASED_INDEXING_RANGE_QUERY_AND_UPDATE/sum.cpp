#include <iostream>
#include <vector>

using namespace std;

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

    void rangeAdd(int l, int r, int delta) {
        add(l, delta);
        add(r + 1, -delta);
    }
};

int main() {
    // Example usage
    vector<int> arr = {1, 2, 3, 4, 5};

    int n = arr.size();

    FenwickTree tree(arr);

    // Perform a range query
    int sum = tree.sum(1, 3);
    cout << "Sum in range [1, 3]: " << sum << endl;

    //
