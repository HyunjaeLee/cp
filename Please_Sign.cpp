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

void solve() {
    int N;
    cin >> N;
    vector<i64> A(N);
    read(A);
    vector<vector<int>> adj(N);
    for (auto i = 1; i < N; ++i) {
        int p;
        cin >> p;
        --p;
        adj[p].push_back(i);
    }
    vector<int> depth(N);
    [&](this auto &&self, int u) -> void {
        for (auto v : adj[u]) {
            depth[v] = depth[u] + 1;
            self(v);
        }
    }(0);
    vector<i64> F(N);
    for (auto i = 0; i < N; ++i) {
        F[depth[i]] += A[i];
    }
    for (auto i = N - 1; 0 <= i; --i) {
        if (F[i] < 0) {
            cout << "-";
            return;
        } else if (0 < F[i]) {
            cout << "+";
            return;
        }
    }
    cout << "0";
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
