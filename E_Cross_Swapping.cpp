#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

#ifndef XOR_HPP
#define XOR_HPP

// Xor Abelian Group
template <typename T> struct Xor {
    T val;
    static Xor op(Xor a, Xor b) { return {a.val ^ b.val}; }
    static Xor e() { return {0}; }
    static Xor inv(Xor x) { return x; }
    friend bool operator==(const Xor &a, const Xor &b) { return a.val == b.val; }
};

#endif // XOR_HPP

#ifndef POTENTIALIZED_ROLLBACK_DSU
#define POTENTIALIZED_ROLLBACK_DSU

#include <algorithm>
#include <cassert>
#include <tuple>
#include <vector>

// A is an abelian group
template <typename A> struct PotentializedRollbackDSU {
    explicit PotentializedRollbackDSU(int n) : n_(n), valid_(true), parent_or_size_(n, -1), potential_(n, A::e()) {}
    int leader(int u) const { return parent_or_size_[u] < 0 ? u : leader(parent_or_size_[u]); }
    // returns p_u
    A potential(int u) const {
        return parent_or_size_[u] < 0 ? A::e() : A::op(potential_[u], potential(parent_or_size_[u]));
    }
    // returns p_v - p_u
    A diff(int u, int v) const {
        auto p_u = potential(u);
        auto p_v = potential(v);
        return A::op(p_v, A::inv(p_u));
    }
    // returns history accumulation count for offline dynamic connectivity
    // p_u + w = p_v
    int merge(int u, int v, A w) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        auto p_v = A::op(A::op(potential(u), w), A::inv(potential(v)));
        u = leader(u);
        v = leader(v);
        if (u == v) {
            history_.emplace_back(-1, 0, valid_);
            if (!(p_v == A::e())) {
                valid_ = false;
            }
            return 1;
        }
        // insert tree v into tree u
        if (-parent_or_size_[u] < -parent_or_size_[v]) {
            std::swap(u, v);
            p_v = A::inv(p_v);
        }
        history_.emplace_back(v, parent_or_size_[v], valid_);
        parent_or_size_[u] += parent_or_size_[v];
        parent_or_size_[v] = u;
        potential_[v] = p_v;
        return 1;
    }
    bool same(int u, int v) const {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        return leader(u) == leader(v);
    }
    int size(int u) const {
        assert(0 <= u && u < n_);
        return -parent_or_size_[leader(u)];
    }
    void rollback() {
        assert(!history_.empty());
        auto [v, size, valid] = history_.back();
        if (~v) {
            auto u = parent_or_size_[v];
            parent_or_size_[v] = size;
            parent_or_size_[u] -= size;
            potential_[v] = A::e();
        } else {
            valid_ = valid;
        }
        history_.pop_back();
    }
    void rollback(int count) {
        for (auto i = 0; i < count; ++i) {
            rollback();
        }
    }
    bool is_valid() const { return valid_; }

private:
    int n_;
    bool valid_;
    std::vector<int> parent_or_size_;
    std::vector<A> potential_;
    std::vector<std::tuple<int, int, bool>> history_;
};

#endif // POTENTIALIZED_ROLLBACK_DSU

void solve() {
    int N;
    cin >> N;
    vector<vector<int>> A(N, vector<int>(N));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }
    PotentializedRollbackDSU<Xor<int>> dsu(N);
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            if (A[j][i] < A[i][j]) {
                dsu.merge(i, j, {1});
            } else if (A[i][j] < A[j][i]) {
                dsu.merge(i, j, {0});
            }
            if (!dsu.is_valid()) {
                dsu.rollback();
            }
        }
    }
    assert(dsu.is_valid());
    for (auto i = 0; i < N - 1; ++i) {
        for (auto j = i + 1; j < N; ++j) {
            if (dsu.potential(i).val ^ dsu.potential(j).val) {
                swap(A[i][j], A[j][i]);
            }
        }
    }
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            cout << A[i][j] << " \n"[j == N - 1];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
