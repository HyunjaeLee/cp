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

#include <atcoder/fenwicktree>

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<i64> A(N), B(N);
    read(A);
    read(B);
    vector<vector<pair<int, i64>>> G(N + 1);
    for (auto i = 0; i < N; ++i) {
        auto u = i;
        auto v = (i + 1) % N;
        auto w = A[i];
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    for (auto i = 0; i < N; ++i) {
        auto u = i;
        auto v = N;
        auto w = B[i];
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    constexpr auto inf = numeric_limits<i64>::max() / 4;
    vector<i64> dist(N + 1, inf);
    dist[N] = 0;
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> pq;
    pq.emplace(dist[N], N);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u])
            continue;
        for (auto [v, w] : G[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    atcoder::fenwick_tree<i64> ft(N);
    for (auto i = 0; i < N; ++i) {
        ft.add(i, A[i]);
    }
    while (Q--) {
        int s, t;
        cin >> s >> t;
        --s, --t;
        i64 ans;
        if (t == N) {
            ans = dist[s];
        } else {
            auto d1 = dist[s] + dist[t];
            auto d2 = ft.sum(s, t);
            auto d3 = ft.sum(0, N) - d2;
            ans = min({d1, d2, d3});
        }
        cout << ans << "\n";
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
