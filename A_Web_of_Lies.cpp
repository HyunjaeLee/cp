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
    vector<set<int>> F(N);
    auto Add = [&](int u, int v) {
        F[v].insert(u);
        F[u].insert(v);
    };
    auto Erase = [&](int u, int v) {
        F[v].erase(u);
        F[u].erase(v);
    };
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        Add(u, v);
    }
    set<int> alive;
    auto Touch = [&](int i) {
        auto it = F[i].rbegin();
        if (it == F[i].rend() || *it < i) {
            alive.insert(i);
        } else {
            if (alive.contains(i)) {
                alive.erase(i);
            }
        }
    };
    for (auto i = 0; i < N; ++i) {
        Touch(i);
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            Add(u, v);
            Touch(u);
            Touch(v);
        } else if (t == 2) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            Erase(u, v);
            Touch(u);
            Touch(v);
        } else {
            cout << size(alive) << "\n";
        }
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
