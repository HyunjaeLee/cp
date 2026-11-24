#include <atcoder/lazysegtree>
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

template <typename T> vector<int> cartesian_tree(const vector<T> &a, auto comp) {
    const auto n = int(a.size());
    vector<int> parent(n, -1), st;
    for (auto i = 0; i < n; ++i) {
        auto v = -1;
        while (!st.empty() && comp(a[i], a[st.back()])) {
            v = st.back();
            st.pop_back();
        }
        if (!st.empty()) {
            parent[i] = st.back();
        }
        if (~v) {
            parent[v] = i;
        }
        st.push_back(i);
    }
    return parent;
}

auto inf = numeric_limits<i64>::max() / 4;
i64 op(i64 a, i64 b) { return min(a, b); }
i64 e() { return inf; }
i64 mapping(i64 f, i64 x) { return f + x; }
i64 composition(i64 f, i64 g) { return f + g; }
i64 id() { return 0; }

void solve() {
    int N;
    cin >> N;
    vector<i64> A(N);
    read(A);
    vector<vector<tuple<int, int, i64>>> event(N);
    { // min cartesian tree
        auto parent = cartesian_tree(A, less());
        vector<array<int, 2>> tree(N, {-1, -1});
        auto root = -1;
        for (auto i = 0; i < N; ++i) {
            if (parent[i] == -1) {
                root = i;
            } else if (i < parent[i]) {
                tree[parent[i]][0] = i;
            } else {
                tree[parent[i]][1] = i;
            }
        }
        [&](this auto &&self, int u) -> int {
            if (u == -1)
                return 0;
            auto a = self(tree[u][0]);
            auto b = self(tree[u][1]);
            auto l = u - a - 1;
            auto r = u + b + 1;
            if (0 <= l) {
                auto delta = A[u] - A[l];
                event[l].emplace_back(u, r, delta);
            }
            return a + 1 + b;
        }(root);
    }
    { // max cartesian tree
        auto parent = cartesian_tree(A, greater());
        vector<array<int, 2>> tree(N, {-1, -1});
        auto root = -1;
        for (auto i = 0; i < N; ++i) {
            if (parent[i] == -1) {
                root = i;
            } else if (i < parent[i]) {
                tree[parent[i]][0] = i;
            } else {
                tree[parent[i]][1] = i;
            }
        }
        [&](this auto &&self, int u) -> int {
            if (u == -1)
                return 0;
            auto a = self(tree[u][0]);
            auto b = self(tree[u][1]);
            auto l = u - a - 1;
            auto r = u + b + 1;
            if (0 <= l) {
                auto delta = A[l] - A[u];
                event[l].emplace_back(u, r, delta);
            }
            return a + 1 + b;
        }(root);
    }
    vector<i64> dp(N + 1);
    atcoder::lazy_segtree<i64, op, e, i64, mapping, composition, id> seg(N);
    for (auto i = N - 1; 0 <= i; --i) {
        for (auto [u, r, delta] : event[i]) {
            seg.apply(u, r, delta);
        }
        dp[i] = seg.prod(i + 1, N);
        seg.set(i, dp[i + 1]);
    }
    cout << dp[0] << "\n";
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
