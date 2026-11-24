#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <int I = 0> void read(auto &a) { for (auto &x : a) { cin >> x; if constexpr (I) { x -= I; } } }
template <int I = 0> void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; if constexpr (I) { x += I; } cout << x; } cout << end;
}
// clang-format on

#ifndef SPARSE_SEGTREE_2D_HPP
#define SPARSE_SEGTREE_2D_HPP

#include <algorithm>
#include <cassert>
#include <numeric>
#include <tuple>
#include <vector>

// https://github.com/Aeren1564/CP/blob/master/Library/Data_Structure/Segment_Tree/segment_tree_2d_sparse.sublime-snippet
// https://github.com/maspypy/library/blob/main/ds/segtree/segtree_2d.hpp
template <typename IndexType, class S, auto op, auto e, bool Compress = true> struct sparse_segtree_2d {
    sparse_segtree_2d(const std::vector<IndexType> &x, const std::vector<IndexType> &y)
        : sparse_segtree_2d(int(x.size()), [&](int i) { return std::tuple{x[i], y[i], e()}; }) {}
    sparse_segtree_2d(const std::vector<IndexType> &x, const std::vector<IndexType> &y, const std::vector<S> &data)
        : sparse_segtree_2d(int(x.size()), [&](int i) { return std::tuple{x[i], y[i], data[i]}; }) {}
    // f(i) = (x, y, val)
    sparse_segtree_2d(int n, auto f) : n_(n) {
        std::vector<IndexType> x(n), y(n);
        std::vector<S> wt(n);
        for (auto i = 0; i < n; ++i) {
            auto [a, b, c] = f(i);
            x[i] = a, y[i] = b, wt[i] = c;
        }
        if constexpr (Compress) {
            key_x_ = x;
            std::sort(key_x_.begin(), key_x_.end());
            key_x_.erase(std::unique(key_x_.begin(), key_x_.end()), key_x_.end());
            nx_ = int(key_x_.size());
        } else {
            min_x_ = (x.empty() ? 0 : *std::min_element(x.begin(), x.end()));
            nx_ = (x.empty() ? 1 : *std::max_element(x.begin(), x.end()) - min_x_ + 1);
        }
        log_ = 0;
        while ((1 << log_) < nx_) {
            ++log_;
        }
        size_ = 1 << log_;
        std::vector<int> ix(n);
        for (auto i = 0; i < n; ++i) {
            ix[i] = xtoi(x[i]);
        }
        indptr_.assign(2 * size_, 0);
        for (auto i : ix) {
            for (i += size_; i; i >>= 1) {
                ++indptr_[i];
            }
        }
        indptr_.insert(indptr_.begin(), 0);
        for (auto i = 1; i < int(indptr_.size()); ++i) {
            indptr_[i] += indptr_[i - 1];
        }
        data_.assign(2 * indptr_.back(), e());
        to_left_.assign(indptr_[size_], 0);
        std::vector<int> ptr = indptr_;
        std::vector<int> I(y.size());
        std::iota(I.begin(), I.end(), 0);
        std::sort(I.begin(), I.end(), [&](int i, int j) { return y[i] < y[j]; });
        pos_.resize(n);
        for (auto i = 0; i < n; ++i) {
            pos_[I[i]] = i;
        }
        for (auto raw_idx : I) {
            int i = ix[raw_idx] + size_;
            int j = -1;
            for (; i; i >>= 1) {
                int p = ptr[i];
                ptr[i]++;
                data_[indptr_[i + 1] + p] = wt[raw_idx];
                if (j != -1) {
                    to_left_[p] = (j % 2 == 0);
                }
                j = i;
            }
        }
        to_left_.insert(to_left_.begin(), 0);
        for (auto i = 1; i < int(to_left_.size()); ++i) {
            to_left_[i] += to_left_[i - 1];
        }
        for (auto i = 0; i < 2 * size_; ++i) {
            int off = 2 * indptr_[i];
            int m = indptr_[i + 1] - indptr_[i];
            for (auto j = m - 1; 0 < j; --j) {
                data_[off + j] = op(data_[off + 2 * j + 0], data_[off + 2 * j + 1]);
            }
        }
        all_y_ = y;
        std::sort(all_y_.begin(), all_y_.end());
    }
    // raw_idx: index in the original point cloud
    void multiply(int raw_idx, S val) {
        assert(0 <= raw_idx && raw_idx < n_);
        int i = 1, p = pos_[raw_idx];
        while (true) {
            multiply_i(i, p - indptr_[i], val);
            if (size_ <= i) {
                break;
            }
            int lc = to_left_[p] - to_left_[indptr_[i]];
            int rc = (p - indptr_[i]) - lc;
            if (to_left_[p + 1] - to_left_[p]) {
                p = indptr_[2 * i + 0] + lc;
                i = 2 * i + 0;
            } else {
                p = indptr_[2 * i + 1] + rc;
                i = 2 * i + 1;
            }
        }
    }
    // raw_idx: index in the original point cloud
    void set(int raw_idx, S val) {
        assert(0 <= raw_idx && raw_idx < n_);
        int i = 1, p = pos_[raw_idx];
        while (true) {
            set_i(i, p - indptr_[i], val);
            if (size_ <= i) {
                break;
            }
            int lc = to_left_[p] - to_left_[indptr_[i]];
            int rc = (p - indptr_[i]) - lc;
            if (to_left_[p + 1] - to_left_[p]) {
                p = indptr_[2 * i + 0] + lc;
                i = 2 * i + 0;
            } else {
                p = indptr_[2 * i + 1] + rc;
                i = 2 * i + 1;
            }
        }
    }
    // [lx, rx) * [ly, ry)
    // O(log^2 n)
    S prod(IndexType lx, IndexType rx, IndexType ly, IndexType ry) const {
        assert(lx <= rx && ly <= ry);
        int L = xtoi(lx);
        int R = xtoi(rx);
        S res = e();
        auto dfs = [&](auto self, int i, int l, int r, int a, int b) -> void {
            if (a == b || R <= l || r <= L) {
                return;
            }
            if (L <= l && r <= R) {
                res = op(res, query_i(i, a, b));
                return;
            }
            int la = to_left_[indptr_[i] + a] - to_left_[indptr_[i]];
            int ra = a - la;
            int lb = to_left_[indptr_[i] + b] - to_left_[indptr_[i]];
            int rb = b - lb;
            int m = (l + r) / 2;
            self(self, 2 * i + 0, l, m, la, lb);
            self(self, 2 * i + 1, m, r, ra, rb);
        };
        dfs(dfs, 1, 0, size_, int(std::lower_bound(all_y_.begin(), all_y_.end(), ly) - all_y_.begin()),
            int(std::lower_bound(all_y_.begin(), all_y_.end(), ry) - all_y_.begin()));
        return res;
    }
    // [lx, rx) * [ly, ry)
    // O(log n)
    int count(IndexType lx, IndexType rx, IndexType ly, IndexType ry) const {
        assert(lx <= rx && ly <= ry);
        int L = xtoi(lx);
        int R = xtoi(rx);
        int res = 0;
        auto dfs = [&](auto self, int i, int l, int r, int a, int b) -> void {
            if (a == b || R <= l || r <= L) {
                return;
            }
            if (L <= l && r <= R) {
                res += b - a;
                return;
            }
            int la = to_left_[indptr_[i] + a] - to_left_[indptr_[i]];
            int ra = a - la;
            int lb = to_left_[indptr_[i] + b] - to_left_[indptr_[i]];
            int rb = b - lb;
            int m = (l + r) / 2;
            self(self, 2 * i + 0, l, m, la, lb);
            self(self, 2 * i + 1, m, r, ra, rb);
        };
        dfs(dfs, 1, 0, size_, int(std::lower_bound(all_y_.begin(), all_y_.end(), ly) - all_y_.begin()),
            int(std::lower_bound(all_y_.begin(), all_y_.end(), ry) - all_y_.begin()));
        return res;
    }

private:
    int xtoi(IndexType x) const {
        if constexpr (Compress) {
            return int(std::lower_bound(key_x_.begin(), key_x_.end(), x) - key_x_.begin());
        }
        return std::clamp<IndexType>(x - min_x_, 0, nx_);
    }
    S query_i(int i, int a, int b) const {
        int lid = indptr_[i];
        int n = indptr_[i + 1] - indptr_[i];
        int off = 2 * lid;
        S val = e();
        for (auto L = n + a, R = n + b; L < R; L >>= 1, R >>= 1) {
            if (L & 1) {
                val = op(val, data_[off + L++]);
            }
            if (R & 1) {
                val = op(data_[off + --R], val);
            }
        }
        return val;
    }
    void multiply_i(int i, int j, S val) {
        int lid = indptr_[i];
        int n = indptr_[i + 1] - indptr_[i];
        int off = 2 * lid;
        for (j += n; j; j >>= 1) {
            data_[off + j] = op(data_[off + j], val);
        }
    }
    void set_i(int i, int j, S val) {
        int lid = indptr_[i];
        int n = indptr_[i + 1] - indptr_[i];
        int off = 2 * lid;
        j += n;
        data_[off + j] = val;
        for (; 0 < (j >>= 1);) {
            data_[off + j] = op(data_[off + 2 * j + 0], data_[off + 2 * j + 1]);
        }
    }
    int n_, nx_, log_, size_;
    IndexType min_x_;
    std::vector<IndexType> key_x_, all_y_;
    std::vector<int> pos_, indptr_, to_left_;
    std::vector<S> data_;
};

#endif // SPARSE_SEGTREE_2D_HPP

int op(int, int) { return 0; }

int e() { return 0; }

#define TC
void solve() {
    int N, D;
    cin >> N >> D;
    vector<int> X(N), Y(N);
    for (auto i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        X[i] = x + y;
        Y[i] = x - y;
    }
    sparse_segtree_2d<int, int, op, e> seg(X, Y);
    for (auto i = 0; i < N; ++i) {
        if (seg.count(X[i] + D, X[i] + D + 1, Y[i], Y[i] + 1) &&
            seg.count(X[i], X[i] + D + 1, Y[i] + D, Y[i] + D + 1)) {
            auto p = i, q = -1, r = -1;
            for (auto j = 0; j < N; ++j) {
                if (pair{X[j], Y[j]} == pair{X[i] + D, Y[i]}) {
                    q = j;
                }
                if (X[i] <= X[j] && X[j] <= X[i] + D && Y[j] == Y[i] + D) {
                    r = j;
                }
            }
            cout << p + 1 << " " << q + 1 << " " << r + 1 << "\n";
            return;
        }
        if (seg.count(X[i], X[i] + 1, Y[i] + D, Y[i] + D + 1) &&
            seg.count(X[i] + D, X[i] + D + 1, Y[i], Y[i] + D + 1)) {
            auto p = i, q = -1, r = -1;
            for (auto j = 0; j < N; ++j) {
                if (pair{X[j], Y[j]} == pair{X[i], Y[i] + D}) {
                    q = j;
                }
                if (X[j] == X[i] + D && Y[i] <= Y[j] && Y[j] <= Y[i] + D) {
                    r = j;
                }
            }
            cout << p + 1 << " " << q + 1 << " " << r + 1 << "\n";
            return;
        }
        if (seg.count(X[i] + D, X[i] + D + 1, Y[i], Y[i] + 1) &&
            seg.count(X[i], X[i] + D + 1, Y[i] - D, Y[i] - D + 1)) {
            auto p = i, q = -1, r = -1;
            for (auto j = 0; j < N; ++j) {
                if (pair{X[j], Y[j]} == pair{X[i] + D, Y[i]}) {
                    q = j;
                }
                if (X[i] <= X[j] && X[j] <= X[i] + D && Y[j] == Y[i] - D) {
                    r = j;
                }
            }
            cout << p + 1 << " " << q + 1 << " " << r + 1 << "\n";
            return;
        }
        if (seg.count(X[i], X[i] + 1, Y[i] + D, Y[i] + D + 1) &&
            seg.count(X[i] - D, X[i] - D + 1, Y[i], Y[i] + D + 1)) {
            auto p = i, q = -1, r = -1;
            for (auto j = 0; j < N; ++j) {
                if (pair{X[j], Y[j]} == pair{X[i], Y[i] + D}) {
                    q = j;
                }
                if (X[j] == X[i] - D && Y[i] <= Y[j] && Y[j] <= Y[i] + D) {
                    r = j;
                }
            }
            cout << p + 1 << " " << q + 1 << " " << r + 1 << "\n";
            return;
        }
    }
    cout << "0 0 0\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
