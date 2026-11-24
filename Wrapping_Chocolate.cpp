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
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(N), C(M), D(M);
    read(A);
    read(B);
    read(C);
    read(D);
    vector<pair<int, int>> F(N);
    for (auto i = 0; i < N; ++i) {
        F[i] = {A[i], B[i]};
    }
    vector<pair<int, int>> G(M);
    for (auto i = 0; i < M; ++i) {
        G[i] = {C[i], D[i]};
    }
    ranges::sort(F, greater());
    ranges::sort(G, greater());
    auto it = G.begin();
    multiset<int> S;
    for (auto [x, y] : F) {
        while (it != G.end() && x <= it->first) {
            S.insert(it->second);
            ++it;
        }
        auto lb = S.lower_bound(y);
        if (lb == S.end()) {
            cout << "No\n";
            return;
        }
        S.erase(lb);
    }
    cout << "Yes\n";
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
