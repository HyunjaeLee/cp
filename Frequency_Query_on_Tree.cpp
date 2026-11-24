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

#line 1 "mo/mo_tree.hpp"

#line 1 "mo/hilbert_mo.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

struct HilbertMo {
    HilbertMo(int n) : n_(n), log_(std::bit_width(unsigned(n))) {}
    void add(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        auto index = int(queries_.size());
        auto order = hilbert_order(l, r);
        queries_.push_back({l, r, index, order});
    }
    void solve(auto add, auto remove, auto eval) { solve(add, add, remove, remove, eval); }
    void solve(auto add_left, auto add_right, auto remove_left, auto remove_right, auto eval) {
        sort(queries_.begin(), queries_.end());
        auto l = 0, r = 0;
        for (auto [left, right, index, order] : queries_) {
            while (left < l) {
                add_left(--l);
            }
            while (r < right) {
                add_right(r++);
            }
            while (l < left) {
                remove_left(l++);
            }
            while (right < r) {
                remove_right(--r);
            }
            eval(index);
        }
    }

private:
    struct query {
        int left, right, index;
        long long order;
        bool operator<(const query &other) const { return order < other.order; }
    };
    long long hilbert_order(int x, int y) const {
        auto d = 0LL;
        for (auto s = 1 << log_; s > 0; s >>= 1) {
            bool rx = x & s, ry = y & s;
            d = (d << 2) | ((rx * 3) ^ ry);
            if (!ry) {
                if (rx) {
                    x = ~x;
                    y = ~y;
                }
                std::swap(x, y);
            }
        }
        return d;
    }
    std::vector<query> queries_;
    const int n_, log_;
};

#line 7 "mo/mo_tree.hpp"
#include <utility>
#line 9 "mo/mo_tree.hpp"

struct MoTree {
    explicit MoTree(const std::vector<std::vector<int>> &adj)
        : n_(int(adj.size())), in_(n_), tour_(2 * n_), top_(n_), parent_(n_), mo_(2 * n_) {
        auto timer = 0;
        std::vector<int> size(n_, 1), heavy(n_, -1);
        auto dfs = [&](auto &&self, int u) -> void {
            for (auto v : adj[u]) {
                if (v != parent_[u]) {
                    parent_[v] = u;
                    self(self, v);
                    size[u] += size[v];
                    if (heavy[u] == -1 || size[heavy[u]] < size[v]) {
                        heavy[u] = v;
                    }
                }
            }
        };
        auto hld = [&](auto &&self, int u) -> void {
            in_[u] = timer;
            tour_[timer++] = u;
            for (auto v : adj[u]) {
                if (v != parent_[u]) {
                    top_[v] = (v == heavy[u]) ? top_[u] : v;
                    self(self, v);
                }
            }
            tour_[timer++] = u;
        };
        dfs(dfs, 0);
        hld(hld, 0);
    }
    int lca(int u, int v) const {
        assert(0 <= u && u < n_ && 0 <= v && v <= n_);
        while (top_[u] != top_[v]) {
            if (in_[top_[u]] < in_[top_[v]]) {
                std::swap(u, v);
            }
            u = parent_[top_[u]];
        }
        return (in_[u] < in_[v]) ? u : v;
    }
    void add(int u, int v) {
        assert(0 <= u && u < n_ && 0 <= v && v <= n_);
        lca_.push_back(lca(u, v));
        auto [l, r] = std::minmax(in_[u], in_[v]);
        mo_.add(l + 1, r + 1);
    }
    void solve(auto add, auto remove, auto eval) {
        std::vector<bool> contains(n_);
        auto toggle = [&](int i) {
            auto u = tour_[i];
            if (contains[u]) {
                remove(u);
            } else {
                add(u);
            }
            contains[u].flip();
        };
        auto eval_lca = [&](int i) {
            toggle(in_[lca_[i]]);
            eval(i);
            toggle(in_[lca_[i]]);
        };
        mo_.solve(toggle, toggle, eval_lca);
    }

private:
    int n_;
    std::vector<int> in_, tour_, top_, parent_, lca_;
    HilbertMo mo_;
};

#ifndef SQRT_FREQ_TABLE_HPP
#define SQRT_FREQ_TABLE_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

struct SqrtFreqTable {
    explicit SqrtFreqTable(int max_val)
        : m_(std::max(1, max_val)), b_sz_(int(std::sqrt(m_))), freq_(m_ + 1), bucket_(m_ / b_sz_ + 1) {}
    void insert(int x) { // O(1)
        assert(0 <= x && x <= m_);
        ++freq_[x];
        ++bucket_[x / b_sz_];
        ++total_;
        distinct_ += int(freq_[x] == 1);
    }
    void erase(int x) { // O(1)
        assert(0 <= x && x <= m_);
        assert(0 < freq_[x]);
        --freq_[x];
        --bucket_[x / b_sz_];
        --total_;
        distinct_ -= int(freq_[x] == 0);
    }
    int count(int x) const { // O(1)
        assert(0 <= x && x <= m_);
        return freq_[x];
    }
    int size() const { return total_; }
    int count_distinct() const { return distinct_; }
    int kth(int k) const { // O(sqrt(M)), 0-indexed
        auto cnt = 0;
        for (auto i = 0; i < m_ / b_sz_ + 1; ++i) {
            if (cnt + bucket_[i] <= k) {
                cnt += bucket_[i];
                continue;
            }
            auto x = i * b_sz_;
            while ((cnt += freq_[x]) <= k) {
                ++x;
            }
            return x;
        }
        return -1;
    };
    int rank(int x) const { // O(sqrt(M)), count y s.t. y < x
        if (x < 0) {
            return 0;
        }
        if (m_ < x) {
            return total_;
        }
        auto cnt = 0;
        for (auto i = 0; i < x / b_sz_; ++i) {
            cnt += bucket_[i];
        }
        for (auto i = x / b_sz_ * b_sz_; i < x; ++i) {
            cnt += freq_[i];
        }
        return cnt;
    }

private:
    const int m_, b_sz_;
    std::vector<int> freq_, bucket_;
    int total_ = 0, distinct_ = 0;
};

#endif // SQRT_FREQ_TABLE_HPP

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    read<1>(A);
    vector<vector<int>> G(N);
    for (auto i = 1; i < N; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<array<int, 4>> qs(Q);
    for (auto &[u, v, l, r] : qs) {
        cin >> u >> v >> l >> r;
        --u, --v, ++r;
    }
    MoTree mo(G);
    for (auto [u, v, l, r] : qs) {
        mo.add(u, v);
    }
    vector<int> ans(Q);
    vector<int> freq(N);
    SqrtFreqTable S(N + 1);
    for (auto i = 0; i < N; ++i) {
        S.insert(0);
    }
    auto add = [&](int u) {
        auto &f = freq[A[u]];
        S.erase(f);
        S.insert(++f);
    };
    auto remove = [&](int u) {
        auto &f = freq[A[u]];
        S.erase(f);
        S.insert(--f);
    };
    auto eval = [&](int i) {
        auto [u, v, l, r] = qs[i];
        ans[i] = S.rank(r) - S.rank(l);
    };
    mo.solve(add, remove, eval);
    show(ans, "\n", "");
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
