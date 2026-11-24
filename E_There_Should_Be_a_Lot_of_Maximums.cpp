#define NDEBUG
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

#ifndef ROLLBACK_MO_HPP
#define ROLLBACK_MO_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>

struct RollbackMo {
    explicit RollbackMo(int n) : n_(n) {}
    void add(int l, int r) { // [l, r)
        assert(0 <= l && l <= r && r <= n_);
        queries_.emplace_back(l, r);
    }
    void solve(auto add, auto rollback, auto eval) { solve(add, add, rollback, eval); }
    void solve(auto add_left, auto add_right, auto rollback, auto eval) {
        const auto q = int(queries_.size());
        if (q == 0) {
            return;
        }
        const auto b_num = int(std::sqrt(q));
        const auto b_sz = (n_ + b_num - 1) / b_num;
        std::vector<std::vector<int>> buckets((n_ - 1) / b_sz + 1);
        auto rollback_n = [&](int n) {
            for (auto i = 0; i < n; ++i) {
                rollback();
            }
        };
        auto naive = [&](int qid) {
            auto [l, r] = queries_[qid];
            for (auto i = l; i < r; ++i) {
                add_right(i);
            }
            eval(qid);
            rollback_n(r - l);
        };
        for (auto qid = 0; qid < q; ++qid) {
            auto [l, r] = queries_[qid];
            auto il = l / b_sz, ir = r / b_sz;
            if (il == ir) {
                naive(qid);
            } else {
                buckets[il].push_back(qid);
            }
        }
        for (auto &bucket : buckets) {
            if (bucket.empty()) {
                continue;
            }
            std::ranges::sort(bucket, {}, [&](int i) { return queries_[i].second; });
            auto lmax = 0;
            for (auto qid : bucket) {
                auto [l, r] = queries_[qid];
                lmax = std::max(lmax, l);
            }
            auto l = lmax, r = lmax;
            for (auto qid : bucket) {
                auto [ql, qr] = queries_[qid];
                while (r < qr) {
                    add_right(r++);
                }
                while (ql < l) {
                    add_left(--l);
                }
                eval(qid);
                rollback_n(lmax - l);
                l = lmax;
            }
            rollback_n(r - l);
        }
    }

private:
    int n_;
    std::vector<std::pair<int, int>> queries_;
};

#endif // ROLLBACK_MO_HPP

void solve() {
    int N;
    cin >> N;
    vector<vector<pair<int, int>>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }
    vector<int> A(N);
    read(A);
    auto X = A;
    ranges::sort(X);
    X.erase(unique(begin(X), end(X)), end(X));
    auto timer = 0;
    vector<int> in(N), out(N), eid(N);
    [&](this auto &&self, int u, int p) -> void {
        in[u] = timer++;
        for (auto [v, i] : adj[u]) {
            if (v != p) {
                eid[v] = i;
                self(v, u);
            }
        }
        out[u] = timer;
    }(0, 0);
    vector<int> S(2 * N);
    for (auto i = 0; i < N; ++i) {
        auto it = ranges::lower_bound(X, A[i]);
        S[in[i] + N] = S[in[i]] = int(it - begin(X));
    }
    vector<int> ans(N - 1, -1);
    vector<pair<int, int>> history; // (old mad, x)
    auto mad = -1;
    vector<int> freq(X.size());
    auto add = [&](int i) {
        history.emplace_back(mad, S[i]);
        if (++freq[S[i]] == 2) {
            mad = max(mad, S[i]);
        }
    };
    auto rollback = [&] {
        auto [old, x] = history.back();
        history.pop_back();
        mad = old;
        --freq[x];
    };
    auto eval = [&](int qid) {
        auto i = qid / 2 + 1;
        ans[eid[i]] = max(ans[eid[i]], mad);
    };
    RollbackMo mo(2 * N);
    for (auto i = 1; i < N; ++i) {
        mo.add(in[i], out[i]);
        mo.add(out[i], N + in[i]);
    }
    mo.solve(add, rollback, eval);
    for (auto i = 0; i < N - 1; ++i) {
        cout << (ans[i] == -1 ? 0 : X[ans[i]]) << "\n";
    }
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
