#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <climits>

using namespace std;
using namespace chrono;

class SegmentTree {
public:
    SegmentTree(const vector<int>& arr) : arr(arr), st(4 * arr.size()) {}

    void build() {
        build(0, 0, arr.size() - 1);
    }

    int query(int l, int r) {
        return query(0, 0, arr.size() - 1, l, r);
    }

    void update(int idx, int val) {
        update(0, 0, arr.size() - 1, idx, val);
    }

    int get(int idx) {
        return arr[idx];
    }

private:
    vector<int> arr;
    vector<int> st;

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

    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) {
            return 0;
        }

        if (ql <= l && qr >= r) {
            return st[node];
        }

        int mid = (l + r) / 2;
        return query(2 * node + 1, l, mid, ql, qr) +
               query(2 * node + 2, mid + 1, r, ql, qr);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (idx < l || idx > r) {
            return;
        }

        if (l == r) {
            st[node] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (idx <= mid) {
            update(2 * node + 1, l, mid, idx, val);
        } else {
            update(2 * node + 2, mid + 1, r, idx, val);
        }

        st[node] = st[2 * node + 1] + st[2 * node + 2];
    }
};

class SegmentTreeLazy {
public:
    SegmentTreeLazy(const vector<int>& arr) : arr(arr), st(4 * arr.size()), lazy(4 * arr.size()) {}

    void build() {
        build(0, 0, arr.size() - 1);
    }

    int query(int l, int r) {
        return query(0, 0, arr.size() - 1, l, r);
    }

    void update(int l, int r, int val) {
        update(0, 0, arr.size() - 1, l, r, val);
    }

    int get(int idx) {
        return arr[idx];
    }

    int query_min(int l, int r) {
        return query_min(0, 0, arr.size() - 1, l, r);
    }

    int query_max(int l, int r) {
        return query_max(0, 0, arr.size() - 1, l, r);
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

    int query(int node, int l, int r, int ql, int qr) {
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
        return query(2 * node + 1, l, mid, ql, qr) +
               query(2 * node + 2, mid + 1, r, ql, qr);
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
};

int main() {
    int n, c;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    cout << "Enter the choice (1: Construction time, 2: Range minimum query, 3: Range maximum query, 4: Range update): ";
    cin >> c;

    vector<int> arr(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    auto start = high_resolution_clock::now();
    SegmentTree seg(arr);
    seg.build();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    if (c == 1) {
        cout << "Segment Tree (without lazy propagation) construction time: " << duration.count() << " nanoseconds" << endl;
        start = high_resolution_clock::now();
        SegmentTreeLazy stl(arr);
        stl.build();
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout << "Segment Tree (with lazy propagation) construction time: " << duration.count() << " nanoseconds" << endl;
    } else if (c == 2) {
        int l, r;
        cout << "Enter the range (l, r): ";
        cin >> l >> r;
        start = high_resolution_clock::now();
        SegmentTreeLazy stl(arr);
        stl.build();
        int min_val = stl.query_min(l, r);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout << "Range minimum query time: " << duration.count() << " nanoseconds" << endl;
        cout << "Range minima: " << min_val << endl;
    } else if (c == 3) {
        int l, r;
        cout << "Enter the range (l, r): ";
        cin >> l >> r;
        start = high_resolution_clock::now();
        SegmentTreeLazy stl(arr);
        stl.build();
        int max_val = stl.query_max(l, r);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout << "Range maximum query time: " << duration.count() << " nanoseconds" << endl;
        cout << "Range maxima: " << max_val << endl;
    } else if (c == 4) {
        int l, r, val;
        cout << "Enter the range (l, r) and value: ";
        cin >> l >> r >> val;
        start = high_resolution_clock::now();
        SegmentTreeLazy stl(arr);
        stl.build();
        stl.update(l, r, val);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout << "Segment Tree (with lazy propagation) update efficiency: " << duration.count() << " nanoseconds" << endl;
    }

    return 0;
}
