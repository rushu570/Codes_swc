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
            update(i, a[i]);
    }

    int query(int r) {
        int sum = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            sum += bit[r];
        return sum;
    }

    int query(int l, int r) {
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }

    void update(int idx, int value) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += value;
    }

    void rangeUpdate(int l, int r, int value) {
        update(l, value);
        if (r + 1 < n)
            update(r + 1, -value);
    }
};

int main() {
    // Example usage
    vector<int> arr = {1, 3, 2, 5, 4};

    int n = arr.size();

    FenwickTree tree(arr);

    // Perform a range query
    int sum_val = tree.query(1, 3);
    cout << "Sum in range [1, 3]: " << sum_val << endl;

    // Perform a range update
    tree.rangeUpdate(2, 4, 2);

    // Perform a range query after update
    sum_val = tree.query(1, 3);
    cout << "Sum in range [1, 3] after update: " << sum_val << endl;

    return 0;
}
