#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

void solve() {
    int N, D;
    cin >> N >> D;
    vector<vector<int>> G(N);
    set<pair<int, int>> E;
    for (auto d = 1; d <= D; ++d) {
        for (auto i = 0; i < N; ++i) {
            auto j = (i + d) % N;
            if (i != j) {
                E.insert(minmax(i, j));
            }
        }
    }
    if (int(E.size()) < D * N) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    for (auto [u, v] : E) {
        cout << u + 1 << ' ' << v + 1 << '\n';
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
