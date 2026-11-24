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

#define TC
void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        adj[b].push_back(a);
    }
    constexpr auto inf = numeric_limits<int>::max() / 2;
    vector<int> freq(N, inf);
    freq[0] = 1;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (auto v : adj[u]) {
            if (freq[u] + 1 < freq[v]) {
                freq[v] = freq[u] + 1;
                q.push(v);
            }
        }
    }
    for (auto i = 0; i < N; ++i) {
        if (inf <= freq[i]) {
            cout << "INFINITE\n";
            return;
        }
    }
    cout << "FINITE\n";
    auto F = ranges::max(freq);
    vector<vector<int>> G(F + 1);
    for (auto i = 0; i < N; ++i) {
        G[freq[i]].push_back(i);
    }
    vector<int> A;
    for (auto i = F; 1 <= i; --i) {
        for (auto j = i; j <= F; ++j) {
            A.insert(A.end(), G[j].begin(), G[j].end());
        }
    }
    cout << A.size() << "\n";
    show<1>(A);
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
