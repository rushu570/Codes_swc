#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, numeric_limits<int>::max());
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            update(i, a[i]);
    }

    void update(int idx, int value) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = min(bit[idx], value);
    }

    int query(int r) {
        int min_val = numeric_limits<int>::max();
        for (; r >= 0; r = (r & (r + 1)) - 1)
            min_val = min(min_val, bit[r]);
        return min_val;
    }

    int query(int l, int r) {
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }

    void rangeUpdate(int l, int r, int value) {
        update(l, value);
        if (r + 1 < n)
            update(r + 1, value);
    }
};

int main() {
    // Example usage
    vector<int> arr = {4, 2, 5, 1, 3};

    int n = arr.size();

    FenwickTree tree(arr);

    // Perform a range query
    int min_val = tree.query(1, 3);
    cout << "Minimum in range [1, 3]: " << min_val << endl;

    // Perform a range update
    tree.rangeUpdate(2, 4, -3);

    // Perform a range query after update
    min_val = tree.query(1, 3);
    cout << "Minimum in range [1, 3] after update: " << min_val << endl;

    return 0;
}
