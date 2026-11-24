#include <bits/stdc++.h>
using namespace std;

template <typename T> struct BIT1D {
    vector<T> data;
    BIT1D(int n = 0) : data(n) {}
    void add(int i, T d) { for (; i < ssize(data); i |= i + 1) data[i] += d; }
    T sum(int r) { // [0, r) O(log n)
        T s = 0;
        for (; r; r &= r - 1) s += data[r - 1];
        return s;
    }
    T sum(int l, int r) { return sum(r) - sum(l); } // [l, r) O(log n)
};

template <typename I, typename T> struct BIT2D {
    vector<I> xs;
    vector<vector<I>> ys;
    vector<BIT1D<T>> bit;
    BIT2D(const vector<pair<I, I>> &p) {
        for (auto [x, y] : p) xs.push_back(x);
        ranges::sort(xs), xs.erase(unique(begin(xs), end(xs)), end(xs));
        ys.resize(size(xs));
        for (auto [x, y] : p)
            for (auto i = xtoi(x); i < ssize(xs); i |= i + 1)
                ys[i].push_back(y);
        for (auto &v : ys) {
            ranges::sort(v), v.erase(unique(begin(v), end(v)), end(v));
            bit.emplace_back(size(v));
        }
    }
    // point (x, y) must be in the original point cloud. O(log^2 n)
    void add(I x, I y, T d) {
        for (auto i = xtoi(x); i < ssize(xs); i |= i + 1)
            bit[i].add(ytoi(i, y), d);
    }
    T sum(I x, I y) { // (-inf, x) * (-inf, y) O(log^2 n)
        T s = 0;
        for (auto r = xtoi(x); r; r &= r - 1)
            s += bit[r - 1].sum(ytoi(r - 1, y));
        return s;
    }
    T sum(I x1, I x2, I y1, I y2) { // [x1, x2) * [y1, y2) O(log^2 n)
        return sum(x2, y2) - sum(x1, y2) - sum(x2, y1) + sum(x1, y1);
    }
    int xtoi(I x) { return int(ranges::lower_bound(xs, x) - begin(xs)); }
    int ytoi(int i, I y) { return int(ranges::lower_bound(ys[i], y) - begin(ys[i])); }
};

using i64 = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    vector<pair<int, int>> points(N);
    vector<int> W(N);
    for (auto i = 0; i < N; ++i) {
        auto &[x, y] = points[i];
        cin >> x >> y >> W[i];
    }
    vector<array<int, 5>> query;
    for (auto i = 0; i < Q; ++i) {
        int t;
        cin >> t;
        if (t == 0) {
            int x, y, w;
            cin >> x >> y >> w;
            query.push_back({t, x, y, w, int(points.size())});
            points.emplace_back(x, y);
            W.push_back(w);
        } else {
            int l, d, r, u;
            cin >> l >> d >> r >> u;
            query.push_back({t, l, d, r, u});
        }
    }
    BIT2D<int, i64> bit(points);
    for (auto i = 0; i < N; ++i) {
        auto [x, y] = points[i];
        bit.add(x, y, W[i]);
    }
    for (const auto &q : query) {
        if (q[0] == 0) {
            auto [t, x, y, w, id] = q;
            bit.add(x, y, W[id]);
        } else {
            auto [t, l, d, r, u] = q;
            auto ans = bit.sum(l, r, d, u);
            cout << ans << "\n";
        }
    }
}
