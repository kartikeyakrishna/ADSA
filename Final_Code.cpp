#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <climits>

using namespace std;
using namespace chrono;

class SegmentTree {
public:
    SegmentTree(const vector<int>& arr) : arr(arr), st(4 * arr.size()), lazy(4 * arr.size()) {}

    void build() {
        build(0, 0, arr.size() - 1);
    }

    int query_sum(int l, int r) {
        return query_sum(0, 0, arr.size() - 1, l, r);
    }

    int query_min(int l, int r) {
        return query_min(0, 0, arr.size() - 1, l, r);
    }

    int query_max(int l, int r) {
        return query_max(0, 0, arr.size() - 1, l, r);
    }

    void update(int l, int r, int val) {
        update(0, 0, arr.size() - 1, l, r, val);
    }

    int get(int idx) {
        return arr[idx];
    }

private:
    vector<int> arr;
    vector<int> st;
    vector<int> lazy;

    void build(int node, int l, int r) {
        if (l == r) {
            st[node] = arr[l];
            return;
        }

        int mid = (l + r) / 2;
        build(2 * node + 1, l, mid);
        build(2 * node + 2, mid + 1, r);

        st[node] = st[2 * node + 1] + st[2 * node + 2];
    }

    int query_sum(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) {
            return 0;
        }

        if (lazy[node] != 0) {
            st[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (ql <= l && qr >= r) {
            return st[node];
        }

        int mid = (l + r) / 2;
        return query_sum(2 * node + 1, l, mid, ql, qr) +
               query_sum(2 * node + 2, mid + 1, r, ql, qr);
    }

    int query_min(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) {
            return INT_MAX;
        }

        if (lazy[node] != 0) {
            st[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (ql <= l && qr >= r) {
            return st[node];
        }

        int mid = (l + r) / 2;
        return min(query_min(2 * node + 1, l, mid, ql, qr),
                   query_min(2 * node + 2, mid + 1, r, ql, qr));
    }

    int query_max(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) {
            return INT_MIN;
        }

        if (lazy[node] != 0) {
            st[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (ql <= l && qr >= r) {
            return st[node];
        }

        int mid = (l + r) / 2;
        return max(query_max(2 * node + 1, l, mid, ql, qr),
                   query_max(2 * node + 2, mid + 1, r, ql, qr));
    }

    void update(int node, int l, int r, int ul, int ur, int val) {
        if (ul > r || ur < l) {
            return;
        }

        if (lazy[node] != 0) {
            st[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (ul <= l && ur >= r) {
            st[node] += (r - l + 1) * val;

            if (l != r) {
                lazy[2 * node + 1] += val;
                lazy[2 * node + 2] += val;
            }
            return;
        }

        int mid = (l + r) / 2;
        update(2 * node + 1, l, mid, ul, ur, val);
        update(2 * node + 2, mid + 1, r, ul, ur, val);

        st[node] = st[2 * node + 1] + st[2 * node + 2];
    }
};

int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    auto start = high_resolution_clock::now();
    SegmentTree seg(arr);
    seg.build();
    auto stop = high_resolution_clock::now();
    auto duration_construction = duration_cast<nanoseconds>(stop - start);
    cout << "Segment Tree construction time: " << duration_construction.count() << " nanoseconds" << endl;

    int l, r;
    cout << "Enter the range (l, r): ";
    cin >> l >> r;

    start = high_resolution_clock::now();
    int sum_no_lazy = seg.query_sum(l, r);
    stop = high_resolution_clock::now();
    auto duration_query_sum_no_lazy = duration_cast<nanoseconds>(stop - start);
    cout << "Range sum query time without lazy propagation: " << duration_query_sum_no_lazy.count() << " nanoseconds" << endl;

    start = high_resolution_clock::now();
    int sum_lazy = seg.query_sum(l, r);
    stop = high_resolution_clock::now();
    auto duration_query_sum_lazy = duration_cast<nanoseconds>(stop - start);
    cout << "Range sum query time with lazy propagation: " << duration_query_sum_lazy.count() << " nanoseconds" << endl;

    start = high_resolution_clock::now();
    int min_no_lazy = seg.query_min(l, r);
    stop = high_resolution_clock::now();
    auto duration_query_min_no_lazy = duration_cast<nanoseconds>(stop - start);
    cout << "Range minimum query time without lazy propagation: " << duration_query_min_no_lazy.count() << " nanoseconds" << endl;

    start = high_resolution_clock::now();
    int min_lazy = seg.query_min(l, r);
    stop = high_resolution_clock::now();
    auto duration_query_min_lazy = duration_cast<nanoseconds>(stop - start);
    cout << "Range minimum query time with lazy propagation: " << duration_query_min_lazy.count() << " nanoseconds" << endl;

    start = high_resolution_clock::now();
    int max_no_lazy = seg.query_max(l, r);
    stop = high_resolution_clock::now();
    auto duration_query_max_no_lazy = duration_cast<nanoseconds>(stop - start);
    cout << "Range maximum query time without lazy propagation: " << duration_query_max_no_lazy.count() << " nanoseconds" << endl;

    start = high_resolution_clock::now();
    int max_lazy = seg.query_max(l, r);
    stop = high_resolution_clock::now();
    auto duration_query_max_lazy = duration_cast<nanoseconds>(stop - start);
    cout << "Range maximum query time with lazy propagation: " << duration_query_max_lazy.count() << " nanoseconds" << endl;

    int val;
    cout << "Enter the value for update: ";
    cin >> val;
    start = high_resolution_clock::now();
    seg.update(l, r, val);
    stop = high_resolution_clock::now();
    auto duration_update_no_lazy = duration_cast<nanoseconds>(stop - start);
    cout << "Range update time without lazy propagation: " << duration_update_no_lazy.count() << " nanoseconds" << endl;

    start = high_resolution_clock::now();
    seg.update(l, r, val);
    stop = high_resolution_clock::now();
    auto duration_update_lazy = duration_cast<nanoseconds>(stop - start);
    cout << "Range update time with lazy propagation: " << duration_update_lazy.count() << " nanoseconds" << endl;

    cout << "Range sum without lazy propagation: " << sum_no_lazy << endl;
    cout << "Range sum with lazy propagation: " << sum_lazy << endl;
    cout << "Range minimum without lazy propagation: " << min_no_lazy << endl;
    cout << "Range minimum with lazy propagation: " << min_lazy << endl;
    cout << "Range maximum without lazy propagation: " << max_no_lazy << endl;
    cout << "Range maximum with lazy propagation: " << max_lazy << endl;

    return 0;
}
