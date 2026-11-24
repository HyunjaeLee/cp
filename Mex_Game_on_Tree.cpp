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
    int N, K;
    cin >> N >> K;
    vector<int> parent(N);
    vector<vector<int>> adj(N);
    for (auto i = 1; i < N; ++i) {
        cin >> parent[i];
        parent[i]--;
        adj[parent[i]].push_back(i);
    }
    vector<int> A(N);
    read(A);
    auto alice = false;
    auto mex = [&](vector<int> f) {
        for (auto i = 0; i <= N; ++i) {
            if (f[i] == 0) {
                return i;
            }
        }
        return N + 1;
    };
    [&](this auto &&self, int u) -> pair<int, vector<int>> {
        auto hole = 0;
        vector<int> freq(N + 1);
        if (A[u] == -1) {
            hole = 1;
        } else {
            freq[A[u]] = 1;
        }
        for (auto v : adj[u]) {
            auto [h, f] = self(v);
            hole += h;
            for (auto i = 0; i <= N; ++i) {
                freq[i] += f[i];
            }
        }
        auto cnt = 0;
        for (auto i = 0; i < K; ++i) {
            if (freq[i] == 0) {
                cnt += 1;
            }
        }
        if (hole == 0 && cnt == 0 && mex(freq) == K) {
            alice = true;
        }
        if (hole == 1 && cnt <= 1 && freq[K] == 0) {
            alice = true;
        }
        return {hole, freq};
    }(0);
    cout << (alice ? "Alice" : "Bob") << "\n";
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
