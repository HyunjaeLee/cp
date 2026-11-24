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

#include <atcoder/mincostflow>

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> A(1 << N);
    read(A);
    auto M = ranges::max(A);
    vector<array<int, 3>> E;
    for (auto u = 0; u < (1 << N); ++u) {
        if (popcount(u32(u)) & 1)
            continue;
        for (auto i = 0; i < N; ++i) {
            auto v = u ^ (1 << i);
            E.push_back({(M - A[u]) + (M - A[v]), u, v});
        }
    }
    ranges::sort(E);
    vector<int> V;
    for (auto i = 0; i < min(2 * K * N, int(E.size())); ++i) {
        auto [w, u, v] = E[i];
        V.push_back(u);
        V.push_back(v);
    }
    ranges::sort(V);
    V.erase(unique(begin(V), end(V)), end(V));
    atcoder::mcf_graph<int, int> G(int(V.size()) + 2);
    for (auto i = 0; i < min(2 * K * N, int(E.size())); ++i) {
        auto [w, u, v] = E[i];
        u = int(ranges::lower_bound(V, u) - begin(V));
        v = int(ranges::lower_bound(V, v) - begin(V));
        G.add_edge(u, v, 1, w);
    }
    auto S = int(V.size());
    auto T = int(V.size()) + 1;
    for (auto i = 0; i < int(V.size()); ++i) {
        if (popcount(u32(V[i])) & 1) {
            G.add_edge(i, T, 1, 0);
        } else {
            G.add_edge(S, i, 1, 0);
        }
    }
    auto [f, c] = G.flow(S, T, K);
    auto ans = f * 2 * M - c;
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
