#include <atcoder/maxflow>
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
    string A, B;
    cin >> A >> B;
    auto X = 0;
    for (auto i = 0; i < N; ++i) {
        if (A[i] == B[i]) {
            X |= 1 << i;
        }
    }
    vector<bool> black(1 << N);
    for (auto i = 0; i < M; ++i) {
        string s;
        cin >> s;
        auto x = 0;
        for (auto j = 0; j < N; ++j) {
            if (s[j] == '=') {
                x |= 1 << j;
            }
        }
        black[x] = true;
    }
    auto F = [&] {
        atcoder::mf_graph<int> g((1 << N) + 2);
        auto S = (1 << N);
        auto T = (1 << N) + 1;
        for (auto u = 0; u < (1 << N); ++u) {
            if ((popcount(u32(u)) & 1) || black[u]) {
                continue;
            }
            for (auto i = 0; i < N; ++i) {
                auto v = u ^ (1 << i);
                if (black[v]) {
                    continue;
                }
                g.add_edge(u, v, 1);
            }
        }
        for (auto i = 0; i < (1 << N); ++i) {
            if (popcount(u32(i)) & 1) {
                g.add_edge(i, T, 1);
            } else {
                g.add_edge(S, i, 1);
            }
        }
        return g.flow(S, T);
    };
    auto p = F();
    black[X] = true;
    auto q = F();
    if (q < p) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
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
