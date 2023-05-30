#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, numeric_limits<int>::min());
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            update(i, a[i]);
    }

    void update(int idx, int value) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = max(bit[idx], value);
    }

    int query(int r) {
        int max_val = numeric_limits<int>::min();
        for (; r >= 0; r = (r & (r + 1)) - 1)
            max_val = max(max_val, bit[r]);
        return max_val;
    }

    int query(int l, int r) {
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }
};

int main() {
    // Example usage
    vector<int> arr = {4, 2, 5, 1, 3};

    int n = arr.size();

    FenwickTree tree(arr);

    // Perform a range query
    int max_val = tree.query(1, 3);
    cout << "Maximum in range [1, 3]: " << max_val << endl;

    // Perform a range update
    tree.update(2, 7);

    // Perform a range query after update
    max_val = tree.query(1, 3);
    cout << "Maximum in range [1, 3] after update: " << max_val << endl;

    return 0;
}
