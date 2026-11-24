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

#ifndef CARTESIAN_TREE_HPP
#define CARTESIAN_TREE_HPP

#include <vector>

std::vector<int> cartesian_tree(const std::vector<int> &a) {
    const auto n = int(a.size());
    std::vector<int> parent(n, -1), st;
    for (auto i = 0; i < n; ++i) {
        auto v = -1;
        while (!st.empty() && a[i] < a[st.back()]) {
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

#endif // CARTESIAN_TREE_HPP

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read<1>(A);
    auto parent = cartesian_tree(A);
    auto root = -1;
    vector<vector<int>> G(N);
    for (auto i = 0; i < N; ++i) {
        if (parent[i] == -1) {
            root = i;
        } else {
            G[parent[i]].push_back(i);
        }
    }
    i64 ans = 0;
    auto dfs = [&](this auto &&self, int u) -> int {
        auto sz = 1;
        for (auto v : G[u]) {
            sz += self(v);
        }
        if (G[u].empty()) {
            ans += 1;
        } else if (size(G[u]) == 1) {
            ans += sz;
        } else {
            ans += 2;
        }
        return sz;
    };
    dfs(root);
    cout << ans << "\n";
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
